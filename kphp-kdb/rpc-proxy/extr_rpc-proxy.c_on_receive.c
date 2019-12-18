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
struct TYPE_3__ {int /*<<< orphan*/ * fun_pos; } ;
struct TYPE_4__ {TYPE_1__ methods; } ;

/* Variables and functions */
 TYPE_2__* CC ; 
 size_t RPC_FUN_ON_RECEIVE ; 
 int RPC_FUN_START (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int on_receive (void) {
  return RPC_FUN_START(CC->methods.fun_pos[RPC_FUN_ON_RECEIVE], 0);
}