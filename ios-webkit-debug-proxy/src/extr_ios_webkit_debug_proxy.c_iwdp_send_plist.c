#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* wi_t ;
typedef  TYPE_2__* rpc_t ;
typedef  int /*<<< orphan*/  rpc_status ;
typedef  int /*<<< orphan*/  plist_t ;
typedef  TYPE_3__* iwdp_iwi_t ;
struct TYPE_8__ {TYPE_1__* wi; } ;
struct TYPE_7__ {scalar_t__ state; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* send_plist ) (TYPE_1__*,int /*<<< orphan*/  const) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/  const) ; 

rpc_status iwdp_send_plist(rpc_t rpc, const plist_t rpc_dict) {
  wi_t wi = ((iwdp_iwi_t)rpc->state)->wi;
  return wi->send_plist(wi, rpc_dict);
}