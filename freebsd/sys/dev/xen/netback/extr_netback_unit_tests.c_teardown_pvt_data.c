#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * ifp; int /*<<< orphan*/ * rxs; int /*<<< orphan*/ * txs; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_XENNETBACK ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ *) ; 
 TYPE_1__ xnb_unit_pvt ; 

__attribute__((used)) static void
teardown_pvt_data(void)
{
	if (xnb_unit_pvt.txs != NULL) {
		free(xnb_unit_pvt.txs, M_XENNETBACK);
	}
	if (xnb_unit_pvt.rxs != NULL) {
		free(xnb_unit_pvt.rxs, M_XENNETBACK);
	}
	if (xnb_unit_pvt.ifp != NULL) {
		if_free(xnb_unit_pvt.ifp);
	}
}