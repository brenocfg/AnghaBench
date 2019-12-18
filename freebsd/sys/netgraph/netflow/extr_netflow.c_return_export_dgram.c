#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  priv_p ;
typedef  int /*<<< orphan*/ * item_p ;
typedef  TYPE_2__* fib_export_p ;
struct TYPE_5__ {int /*<<< orphan*/ * item; } ;
struct TYPE_6__ {int /*<<< orphan*/  export_mtx; TYPE_1__ exp; } ;

/* Variables and functions */
 int /*<<< orphan*/  export_send (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
return_export_dgram(priv_p priv, fib_export_p fe, item_p item, int flags)
{

	/*
	 * It may happen on SMP, that some thread has already
	 * put its item there, in this case we bail out and
	 * send what we have to collector.
	 */
	mtx_lock(&fe->export_mtx);
	if (fe->exp.item == NULL) {
		fe->exp.item = item;
		mtx_unlock(&fe->export_mtx);
	} else {
		mtx_unlock(&fe->export_mtx);
		export_send(priv, fe, item, flags);
	}
}