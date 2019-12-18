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
struct repl_handshake_ok {scalar_t__ binlog_slice_start_pos; scalar_t__ binlog_slice_end_pos; scalar_t__ binlog_last_start_pos; scalar_t__ binlog_last_end_pos; scalar_t__ session_id; int /*<<< orphan*/  handshake_id; } ;
struct repl_client_status {int /*<<< orphan*/  flags; scalar_t__ session_id; struct related_binlog* rb; } ;
struct related_binlog {scalar_t__ slice_binlog_pos; scalar_t__ max_binlog_pos; scalar_t__ kfs_replica; } ;
struct connection {int /*<<< orphan*/  remote_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  RC_UPTODATE ; 
 int /*<<< orphan*/  R_ERROR_EBADFD ; 
 int /*<<< orphan*/  R_ERROR_EBADSLICE ; 
 int /*<<< orphan*/  destroy_client (struct repl_client_status*) ; 
 struct repl_client_status* get_client_by_handshake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int send_error (struct connection*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  show_remote_ip (struct connection*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

int process_handshake_ok_packet (struct connection *c, struct repl_handshake_ok *HO) {
  struct repl_client_status *C = get_client_by_handshake (HO->handshake_id, 0);
  vkprintf (2, "received handshake acknowledgement packet from %s:%d, session %d:%d, current slice %lld..%lld, last slice %lld..%lld\n", show_remote_ip (c), c->remote_port, HO->handshake_id, HO->session_id, HO->binlog_slice_start_pos, HO->binlog_slice_end_pos, HO->binlog_last_start_pos, HO->binlog_last_end_pos);
  if (!C) {
    return send_error (c, HO->handshake_id, HO->session_id, R_ERROR_EBADFD, "unknown handshake id");
  }
  if (C->session_id) {
    return send_error (c, HO->handshake_id, HO->session_id, R_ERROR_EBADFD, "handshake already complete for this id");
  }

  struct related_binlog *R = C->rb;
  C->session_id = HO->session_id;

  if (HO->binlog_slice_start_pos > HO->binlog_slice_end_pos || HO->binlog_last_start_pos > HO->binlog_last_end_pos ||
      HO->binlog_last_end_pos < HO->binlog_slice_end_pos || HO->binlog_last_start_pos < HO->binlog_slice_start_pos ||
      HO->binlog_slice_start_pos < 0 || HO->binlog_slice_end_pos < 0 ||
      (HO->binlog_last_start_pos > HO->binlog_slice_start_pos && HO->binlog_last_start_pos < HO->binlog_slice_end_pos)) {
    destroy_client (C);
    return send_error (c, HO->handshake_id, HO->session_id, R_ERROR_EBADSLICE, "invalid binlog start/end positions");
  }

  if (R->kfs_replica) {
    if (R->slice_binlog_pos != HO->binlog_slice_start_pos || R->max_binlog_pos > HO->binlog_slice_end_pos) {
      destroy_client (C);
      return send_error (c, HO->handshake_id, HO->session_id, R_ERROR_EBADSLICE, "binlog start/end positions mismatch: client %lld..%lld, server %lld..%lld", R->slice_binlog_pos, R->max_binlog_pos, HO->binlog_slice_start_pos, HO->binlog_slice_end_pos);
    }
    if (HO->binlog_last_end_pos == R->max_binlog_pos) {
      C->flags |= RC_UPTODATE;
    }
  } else {
    if (HO->binlog_slice_start_pos || HO->binlog_slice_end_pos < 0) {
      destroy_client (C);
      return send_error (c, HO->handshake_id, HO->session_id, R_ERROR_EBADSLICE, "binlog start/end positions mismatch: client %lld..%lld, server %lld..%lld", R->slice_binlog_pos, R->max_binlog_pos, HO->binlog_slice_start_pos, HO->binlog_slice_end_pos);
    }
  }

  return 0;
}