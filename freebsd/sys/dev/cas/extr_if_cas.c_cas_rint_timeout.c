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
struct cas_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAS_LOCK_ASSERT (struct cas_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  cas_rint (struct cas_softc*) ; 

__attribute__((used)) static void
cas_rint_timeout(void *arg)
{
	struct cas_softc *sc = arg;

	CAS_LOCK_ASSERT(sc, MA_OWNED);

	cas_rint(sc);
}