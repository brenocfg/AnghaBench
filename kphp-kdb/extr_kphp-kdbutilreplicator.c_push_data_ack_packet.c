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
struct repl_data_ack {int handshake_id; int session_id; long long binlog_written_pos; long long binlog_received_pos; int /*<<< orphan*/  type; } ;
struct connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  P_REPL_DATA_ACK ; 
 struct repl_data_ack* alloc_packet (int) ; 
 int /*<<< orphan*/  push_packet (struct connection*,int) ; 

__attribute__((used)) static void push_data_ack_packet (struct connection *c, int handshake_id, int session_id, long long pos) {
  struct repl_data_ack *A = alloc_packet (sizeof (struct repl_data_ack));
  A->type = P_REPL_DATA_ACK;
  A->handshake_id = handshake_id;
  A->session_id = session_id;
  A->binlog_written_pos = A->binlog_received_pos = pos;
  push_packet (c, sizeof (struct repl_data_ack));
}