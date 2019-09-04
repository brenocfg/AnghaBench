#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct connection {int /*<<< orphan*/  Out; } ;
struct TYPE_4__ {int /*<<< orphan*/  out_packet_num; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* flush_packet ) (struct connection*) ;} ;

/* Variables and functions */
 int* P ; 
 TYPE_2__* RPCC_DATA (struct connection*) ; 
 TYPE_1__* RPCC_FUNC (struct connection*) ; 
 int RPC_INVOKE_REQ ; 
 int additional ; 
 int /*<<< orphan*/  auth_key_id ; 
 int compute_crc32 (int*,int) ; 
 int /*<<< orphan*/  dump_rpc_packet (int*) ; 
 scalar_t__ expect_input ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_id ; 
 int /*<<< orphan*/  req_id ; 
 int /*<<< orphan*/  session_id ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (struct connection*) ; 
 int verbosity ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,int*,int) ; 

int rpcc_send_query (struct connection *c, int r) {
  req_id++;
  P[0] = 4 * (r + 6 + additional);
  P[1] = RPCC_DATA(c)->out_packet_num++;
  P[2] = RPC_INVOKE_REQ;
  memcpy (&P[3], &req_id, 8);
  if (additional > 0) {
    memcpy (&P[5], &auth_key_id, 8);
    memcpy (&P[7], &session_id, 8);
    msg_id++;
    memcpy (&P[9], &msg_id, 8);
  }
  P[(P[0]/4)-1] = compute_crc32 (P, P[0] - 4);
  write_out (&c->Out, P, P[0]);
  RPCC_FUNC(c)->flush_packet(c);
  if (verbosity >= 4) {
    fprintf (stderr, "Sending:\n");
    dump_rpc_packet (P);
  }
  expect_input = 0;
  return 0;
}