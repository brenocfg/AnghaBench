#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct repl_pos_info {scalar_t__ session_id; long long binlog_time; scalar_t__ binlog_pos; int /*<<< orphan*/  handshake_id; } ;
struct repl_client_status {scalar_t__ session_id; struct related_binlog* rb; } ;
struct related_binlog {TYPE_1__* kfs_replica; int /*<<< orphan*/  replica_name_hash; } ;
struct connection {int /*<<< orphan*/  remote_port; } ;
struct TYPE_2__ {int /*<<< orphan*/  replica_prefix; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_ERROR_EBADFD ; 
 int /*<<< orphan*/  destroy_client (struct repl_client_status*) ; 
 struct repl_client_status* get_client_by_handshake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long long get_precise_time (int) ; 
 int /*<<< orphan*/  posinfo_packets_received ; 
 int send_error (struct connection*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  show_remote_ip (struct connection*) ; 
 int update_binlog_postime_info (int /*<<< orphan*/ ,scalar_t__,long long) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,scalar_t__,long long,int,...) ; 

int process_pos_info_packet (struct connection *c, struct repl_pos_info *RP) {
  posinfo_packets_received++;
  struct repl_client_status *C = get_client_by_handshake (RP->handshake_id, 0);
  vkprintf (2, "received server time packet from %s:%d, session %d:%d, position %lld, time %016llx\n", show_remote_ip (c), c->remote_port, RP->handshake_id, RP->session_id, RP->binlog_pos, RP->binlog_time);
  if (!C) {
    return send_error (c, RP->handshake_id, RP->session_id, R_ERROR_EBADFD, "unknown handshake id");
  }
  if (C->session_id != RP->session_id) {
    destroy_client (C);
    return send_error (c, RP->handshake_id, RP->session_id, R_ERROR_EBADFD, "handshake/session id mismatch");
  }

  long long current_time = get_precise_time (1000000);

  struct related_binlog *R = C->rb;

  if (RP->binlog_time > current_time + (5LL << 32) || RP->binlog_time < current_time - (30LL << 32)) {
    vkprintf (1, "WARNING: server time packet from %s:%d, session %d:%d, position %lld, time %016llx for binlog %s is ignored because of bad time (current time %016llx)\n", show_remote_ip (c), c->remote_port, RP->handshake_id, RP->session_id, RP->binlog_pos, RP->binlog_time, R->kfs_replica->replica_prefix, current_time);
    return 0;
  }

  if ((unsigned long long) RP->binlog_pos > 1LL << 56) {
    vkprintf (1, "WARNING: server time packet from %s:%d, session %d:%d, position %lld, time %016llx for binlog %s is ignored because of bad position\n", show_remote_ip (c), c->remote_port, RP->handshake_id, RP->session_id, RP->binlog_pos, RP->binlog_time, R->kfs_replica->replica_prefix);
    return 0;
  }

  int res = update_binlog_postime_info (R->replica_name_hash, RP->binlog_pos, RP->binlog_time);
  vkprintf (2, "Result of updating binlog position info for replica %s to position %lld, time %016llx is %d\n", R->kfs_replica->replica_prefix, RP->binlog_pos, RP->binlog_time, res);

  return 0;
}