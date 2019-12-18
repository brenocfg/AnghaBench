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
typedef  TYPE_1__* epoch_t ;
struct TYPE_4__ {scalar_t__ e_flags; int /*<<< orphan*/  e_epoch; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_CHECK (TYPE_1__*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  ck_epoch_synchronize_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cold ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  epoch_block_handler ; 

void
epoch_wait(epoch_t epoch)
{

	MPASS(cold || epoch != NULL);
	INIT_CHECK(epoch);
	MPASS(epoch->e_flags == 0);
	critical_enter();
	ck_epoch_synchronize_wait(&epoch->e_epoch, epoch_block_handler, NULL);
	critical_exit();
}