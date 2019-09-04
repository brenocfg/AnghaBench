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
struct connection {int /*<<< orphan*/  Out; int /*<<< orphan*/  fd; int /*<<< orphan*/  In; int /*<<< orphan*/  last_response_time; } ;
struct TYPE_4__ {int /*<<< orphan*/  out_packet_num; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* flush_packet ) (struct connection*) ;} ;

/* Variables and functions */
 TYPE_2__* RPCS_DATA (struct connection*) ; 
 TYPE_1__* RPCS_FUNC (struct connection*) ; 
 int RPC_PING ; 
 int RPC_PONG ; 
 int SKIP_ALL_BYTES ; 
 int /*<<< orphan*/  assert (int) ; 
 int compute_crc32 (int*,int) ; 
 int /*<<< orphan*/  precise_now ; 
 int read_in (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  stub1 (struct connection*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,long long,...) ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,int*,int) ; 

int rpcs_default_execute (struct connection *c, int op, int len) {
  vkprintf (1, "rpcs_execute: fd=%d, op=%d, len=%d\n", c->fd, op, len);
  if (op == RPC_PING && len == 24) {
    c->last_response_time = precise_now;
    static int Q[12];
    assert (read_in (&c->In, Q, 24) == 24);
    static int P[12];
    P[0] = 24;
    P[1] = RPCS_DATA(c)->out_packet_num++;
    P[2] = RPC_PONG;    
    P[3] = Q[3];
    P[4] = Q[4];
    P[5] = compute_crc32 (P, 20);
    vkprintf (1, "Received ping from fd=%d. ping_id = %lld. Sending pong\n", c->fd, *(long long *)(Q + 3));
    write_out (&c->Out, P, 24);
    RPCS_FUNC(c)->flush_packet(c);
    return 24;
  }
  return SKIP_ALL_BYTES;

}