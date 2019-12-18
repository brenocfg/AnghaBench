#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* rpc_t ;
typedef  int /*<<< orphan*/  rpc_status ;
typedef  int /*<<< orphan*/  plist_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* on_reportSetup ) (TYPE_1__*) ;} ;

/* Variables and functions */
 scalar_t__ PLIST_DICT ; 
 int /*<<< orphan*/  RPC_ERROR ; 
 scalar_t__ plist_get_node_type (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

rpc_status rpc_recv_reportSetup(rpc_t self, const plist_t args) {
  if (plist_get_node_type(args) != PLIST_DICT) {
    return RPC_ERROR;
  }
  return self->on_reportSetup(self);
}