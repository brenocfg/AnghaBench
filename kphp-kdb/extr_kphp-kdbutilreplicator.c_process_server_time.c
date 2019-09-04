#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct repl_server_status {int flags; TYPE_2__* conn; int /*<<< orphan*/  session_id; int /*<<< orphan*/  handshake_id; struct related_binlog* rb; int /*<<< orphan*/  buffer; } ;
struct repl_pos_info {int /*<<< orphan*/  binlog_time; int /*<<< orphan*/  binlog_pos; int /*<<< orphan*/  session_id; int /*<<< orphan*/  handshake_id; int /*<<< orphan*/  type; } ;
struct related_binlog {int /*<<< orphan*/  engine_time; int /*<<< orphan*/  engine_log_pos; } ;
struct TYPE_4__ {int /*<<< orphan*/  total_bytes; } ;
struct TYPE_5__ {TYPE_1__ Out; int /*<<< orphan*/  remote_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_PENDING_BYTES_THRESHOLD ; 
 int NOTSENT_SPAM_INTERVAL ; 
 int /*<<< orphan*/  P_REPL_POS_INFO ; 
 int RS_REPL_STARTED ; 
 struct repl_pos_info* alloc_packet (int) ; 
 int now ; 
 int /*<<< orphan*/  posinfo_packets_not_sent ; 
 int /*<<< orphan*/  posinfo_packets_sent ; 
 int /*<<< orphan*/  push_packet (TYPE_2__*,int) ; 
 int /*<<< orphan*/  show_remote_ip (TYPE_2__*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

int process_server_time (struct repl_server_status *S) {
  if (!(S->flags & RS_REPL_STARTED) || !S->buffer) {
    return 0;
  }
  struct related_binlog *R = S->rb;

  if (S->conn->Out.total_bytes > MAX_PENDING_BYTES_THRESHOLD) {
    static int last_spam;
    vkprintf (now / NOTSENT_SPAM_INTERVAL != last_spam ? 0 : 2, 
	      "Server is NOT sending server time packet to %s:%d, session %d:%d, position %lld, time %016llx; %d bytes in output buffer (%lld such errors)\n", 
	      show_remote_ip (S->conn), S->conn->remote_port, S->handshake_id, S->session_id,
	      R->engine_log_pos, R->engine_time, S->conn->Out.total_bytes, posinfo_packets_not_sent);
    posinfo_packets_not_sent++;
    last_spam = now / NOTSENT_SPAM_INTERVAL;
    return 1;
  }
    
  struct repl_pos_info *RP = alloc_packet (sizeof (struct repl_pos_info));
  RP->type = P_REPL_POS_INFO;
  RP->handshake_id = S->handshake_id;
  RP->session_id = S->session_id;
  RP->binlog_pos = R->engine_log_pos;
  RP->binlog_time = R->engine_time;
  posinfo_packets_sent++;
  vkprintf (2, "Server is sending server time packet to %s:%d, session %d:%d, position %lld, time %016llx; %d bytes in output buffer\n", 
	    show_remote_ip (S->conn), S->conn->remote_port, S->handshake_id, S->session_id,
	    RP->binlog_pos, RP->binlog_time, S->conn->Out.total_bytes);
  push_packet (S->conn, sizeof (struct repl_pos_info));

  return 0;
}