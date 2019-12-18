#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  vm_seglist; } ;
typedef  TYPE_1__ vmem_t ;
typedef  int /*<<< orphan*/  bt_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_seglist ; 

__attribute__((used)) static void
bt_insseg(vmem_t *vm, bt_t *bt, bt_t *prev)
{

	TAILQ_INSERT_AFTER(&vm->vm_seglist, prev, bt, bt_seglist);
}