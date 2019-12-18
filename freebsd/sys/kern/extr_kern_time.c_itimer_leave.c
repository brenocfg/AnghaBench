#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct itimer {scalar_t__ it_usecount; int it_flags; int /*<<< orphan*/  it_mtx; } ;

/* Variables and functions */
 int ITF_WANTED ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (struct itimer*) ; 

__attribute__((used)) static void
itimer_leave(struct itimer *it)
{

	mtx_assert(&it->it_mtx, MA_OWNED);
	KASSERT(it->it_usecount > 0, ("invalid it_usecount"));

	if (--it->it_usecount == 0 && (it->it_flags & ITF_WANTED) != 0)
		wakeup(it);
}