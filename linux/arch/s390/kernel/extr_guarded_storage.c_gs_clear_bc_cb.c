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
struct gs_cb {int dummy; } ;
struct TYPE_3__ {struct gs_cb* gs_bc_cb; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 int /*<<< orphan*/  kfree (struct gs_cb*) ; 

__attribute__((used)) static int gs_clear_bc_cb(void)
{
	struct gs_cb *gs_cb;

	gs_cb = current->thread.gs_bc_cb;
	current->thread.gs_bc_cb = NULL;
	kfree(gs_cb);
	return 0;
}