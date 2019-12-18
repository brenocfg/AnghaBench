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
typedef  int /*<<< orphan*/ * epoch_t ;
typedef  TYPE_1__* epoch_record_t ;
struct TYPE_3__ {int /*<<< orphan*/  er_record; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_CHECK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  ck_epoch_begin (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ cold ; 
 int /*<<< orphan*/  critical_enter () ; 
 TYPE_1__* epoch_currecord (int /*<<< orphan*/ *) ; 

void
epoch_enter(epoch_t epoch)
{
	epoch_record_t er;

	MPASS(cold || epoch != NULL);
	INIT_CHECK(epoch);
	critical_enter();
	er = epoch_currecord(epoch);
	ck_epoch_begin(&er->er_record, NULL);
}