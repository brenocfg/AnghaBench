#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct repl_server_status {scalar_t__ handshake_id; scalar_t__ client_log_pos; scalar_t__ client_log_wrpos; scalar_t__ client_log_recvpos; } ;
struct repl_data_ack {scalar_t__ handshake_id; scalar_t__ binlog_written_pos; scalar_t__ binlog_received_pos; int /*<<< orphan*/  session_id; } ;
struct connection {int /*<<< orphan*/  remote_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_ERROR_EBADFD ; 
 int /*<<< orphan*/  R_ERROR_EINVAL ; 
 int /*<<< orphan*/  destroy_server (struct repl_server_status*) ; 
 struct repl_server_status* get_server_by_session (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_server (struct repl_server_status*) ; 
 int send_error (struct connection*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  show_remote_ip (struct connection*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

int process_data_ack_packet (struct connection *c, struct repl_data_ack *A) {
  struct repl_server_status *S = get_server_by_session (A->session_id, 0);
  vkprintf (2, "received data ack packet from %s:%d, session %d:%d, binlog written up to %lld, received up to %lld\n", show_remote_ip (c), c->remote_port, A->handshake_id, A->session_id, A->binlog_written_pos, A->binlog_received_pos);
  if (!S) {
    return send_error (c, A->handshake_id, A->session_id, R_ERROR_EBADFD, "unknown session id");
  }
  if (S->handshake_id != A->handshake_id) {
    destroy_server (S);
    return send_error (c, A->handshake_id, A->session_id, R_ERROR_EBADFD, "handshake/session id mismatch");
  }
  if (A->binlog_written_pos < 0 || A->binlog_received_pos < A->binlog_written_pos) {
    destroy_server (S);
    return send_error (c, A->handshake_id, A->session_id, R_ERROR_EINVAL, "incorrect log positions");
  }
  if (A->binlog_written_pos > S->client_log_pos || A->binlog_written_pos < S->client_log_wrpos || A->binlog_received_pos < S->client_log_recvpos) {
    destroy_server (S);
    return send_error (c, A->handshake_id, A->session_id, R_ERROR_EINVAL, "acknowledged log positions go backwards and/or after the end of transmitted data");
  }
  S->client_log_wrpos = A->binlog_written_pos;
  S->client_log_recvpos = A->binlog_received_pos;
  process_server (S);
  return 0;
}