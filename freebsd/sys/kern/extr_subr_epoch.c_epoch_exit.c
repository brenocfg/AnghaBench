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
typedef  int /*<<< orphan*/  epoch_t ;
typedef  TYPE_1__* epoch_record_t ;
struct TYPE_3__ {int /*<<< orphan*/  er_record; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ck_epoch_end (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  critical_exit () ; 
 TYPE_1__* epoch_currecord (int /*<<< orphan*/ ) ; 

void
epoch_exit(epoch_t epoch)
{
	epoch_record_t er;

	INIT_CHECK(epoch);
	er = epoch_currecord(epoch);
	ck_epoch_end(&er->er_record, NULL);
	critical_exit();
}