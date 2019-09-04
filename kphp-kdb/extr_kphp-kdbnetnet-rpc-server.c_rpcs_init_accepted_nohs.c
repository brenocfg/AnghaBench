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
struct connection {int dummy; } ;
struct TYPE_4__ {int crypto_flags; int in_packet_num; } ;
struct TYPE_3__ {int (* rpc_ready ) (struct connection*) ;} ;

/* Variables and functions */
 TYPE_2__* RPCS_DATA (struct connection*) ; 
 TYPE_1__* RPCS_FUNC (struct connection*) ; 
 int stub1 (struct connection*) ; 

int rpcs_init_accepted_nohs (struct connection *c) {
  RPCS_DATA(c)->crypto_flags = 512 + 1;
  RPCS_DATA(c)->in_packet_num = -3;
  return RPCS_FUNC(c)->rpc_ready ? RPCS_FUNC(c)->rpc_ready (c) : 0;
}