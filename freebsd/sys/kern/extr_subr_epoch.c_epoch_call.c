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
typedef  scalar_t__ epoch_context_t ;
typedef  int /*<<< orphan*/  ck_epoch_entry_t ;
typedef  int /*<<< orphan*/  ck_epoch_cb_t ;
struct TYPE_3__ {int /*<<< orphan*/  er_record; } ;

/* Variables and functions */
 int* DPCPU_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPASS (void (*) (scalar_t__)) ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  ck_epoch_call (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  epoch_cb_count ; 
 TYPE_1__* epoch_currecord (int /*<<< orphan*/ *) ; 
 int inited ; 

void
epoch_call(epoch_t epoch, epoch_context_t ctx, void (*callback) (epoch_context_t))
{
	epoch_record_t er;
	ck_epoch_entry_t *cb;

	cb = (void *)ctx;

	MPASS(callback);
	/* too early in boot to have epoch set up */
	if (__predict_false(epoch == NULL))
		goto boottime;
#if !defined(EARLY_AP_STARTUP)
	if (__predict_false(inited < 2))
		goto boottime;
#endif

	critical_enter();
	*DPCPU_PTR(epoch_cb_count) += 1;
	er = epoch_currecord(epoch);
	ck_epoch_call(&er->er_record, cb, (ck_epoch_cb_t *)callback);
	critical_exit();
	return;
boottime:
	callback(ctx);
}