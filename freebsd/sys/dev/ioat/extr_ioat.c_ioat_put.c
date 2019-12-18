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
struct ioat_softc {int refcnt; int /*<<< orphan*/  submit_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

__attribute__((used)) static void
ioat_put(struct ioat_softc *ioat)
{

	mtx_assert(&ioat->submit_lock, MA_OWNED);
	KASSERT(ioat->refcnt >= 1, ("refcnt error"));

	if (--ioat->refcnt == 0)
		wakeup(&ioat->refcnt);
}