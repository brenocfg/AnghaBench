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
struct connection {int /*<<< orphan*/  Out; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush_packet ) (struct connection*) ;} ;

/* Variables and functions */
 int MAX_PACKET_LEN ; 
 TYPE_1__* RPCS_FUNC (struct connection*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int compute_crc32 (int*,int) ; 
 int /*<<< orphan*/  cr_ok ; 
 int /*<<< orphan*/  server_check_ready (struct connection*) ; 
 int /*<<< orphan*/  stub1 (struct connection*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,int*,int) ; 

int rpc_send_query (void *_R, struct connection *c) {
  int *R = _R;
  vkprintf (4, "sending query... len = %d, op = %x\n", R[0], R[2]);
  vkprintf (6, "c = %p, server_check_ready = %d (cr_ok = %d)\n", c, server_check_ready (c), cr_ok);
  assert (c && server_check_ready (c) == cr_ok);
  assert (R[0] <= MAX_PACKET_LEN && R[0] >= 16 && R[0] % 4 == 0);
  R[(R[0] >> 2) - 1] = compute_crc32 (R, R[0] - 4);
  write_out (&c->Out, R, R[0]);
  RPCS_FUNC(c)->flush_packet (c);
  vkprintf (4, "message_sent\n");
  return 0;
}