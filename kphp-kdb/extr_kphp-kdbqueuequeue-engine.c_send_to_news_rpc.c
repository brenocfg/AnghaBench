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
 int /*<<< orphan*/ * CS ; 
 int CSN ; 
 TYPE_2__* RPCC_DATA (struct connection*) ; 
 TYPE_1__* RPCC_FUNC (struct connection*) ; 
 int /*<<< orphan*/  STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int compute_crc32 (int*,int) ; 
 int dl_abs (int) ; 
 struct connection* get_target_connection (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_failed ; 
 int /*<<< orphan*/  rpc_sent ; 
 int rpc_sent_size ; 
 int /*<<< orphan*/  stub1 (struct connection*) ; 
 int write_out (int /*<<< orphan*/ *,int*,int) ; 

int send_to_news_rpc (int addr, int *q) {
  //fprintf (stderr, "send_to_news_rpc to @%d, [len = %d]\n", addr, q[0]);

  addr = dl_abs (addr) % CSN;
  struct connection *c = get_target_connection (CS[addr]);

  //fprintf (stderr, "connection = %p\n", c);

  if (c == NULL) {
    STAT (rpc_failed);
    return 0;
  }
  STAT (rpc_sent);

  int n = q[0];
  assert (n >= 4);
  q[0] *= sizeof (int);
  q[1] = RPCC_DATA(c)->out_packet_num++;
  q[n - 1] = compute_crc32 (q, q[0] - sizeof (int));

  assert (write_out (&c->Out, q, q[0]) == q[0]);

  rpc_sent_size += q[0];

  //TODO delete it
  RPCC_FUNC(c)->flush_packet(c);
  return 0;
}