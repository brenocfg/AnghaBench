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
struct TYPE_2__ {int /*<<< orphan*/  ifp; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  POLL_ONLY ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int poll_each_burst ; 
 int poll_handlers ; 
 int /*<<< orphan*/  poll_mtx ; 
 TYPE_1__* pr ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ether_poll(int count)
{
	int i;

	mtx_lock(&poll_mtx);

	if (count > poll_each_burst)
		count = poll_each_burst;

	for (i = 0 ; i < poll_handlers ; i++)
		pr[i].handler(pr[i].ifp, POLL_ONLY, count);

	mtx_unlock(&poll_mtx);
}