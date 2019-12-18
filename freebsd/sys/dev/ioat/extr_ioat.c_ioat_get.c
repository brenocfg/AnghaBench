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
struct ioat_softc {scalar_t__ refcnt; int /*<<< orphan*/  submit_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ UINT32_MAX ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ioat_get(struct ioat_softc *ioat)
{

	mtx_assert(&ioat->submit_lock, MA_OWNED);
	KASSERT(ioat->refcnt < UINT32_MAX, ("refcnt overflow"));

	ioat->refcnt++;
}