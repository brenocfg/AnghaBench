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
struct jme_softc {int jme_flags; int /*<<< orphan*/  jme_ostats; int /*<<< orphan*/  jme_stats; } ;
struct jme_hw_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct jme_softc*,int /*<<< orphan*/ ,int) ; 
 int JME_FLAG_HWMIB ; 
 int /*<<< orphan*/  JME_LOCK_ASSERT (struct jme_softc*) ; 
 int /*<<< orphan*/  JME_STATCSR ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
jme_stats_save(struct jme_softc *sc)
{

	JME_LOCK_ASSERT(sc);

	if ((sc->jme_flags & JME_FLAG_HWMIB) == 0)
		return;
	/* Save current counters. */
	bcopy(&sc->jme_stats, &sc->jme_ostats, sizeof(struct jme_hw_stats));
	/* Disable and clear counters. */
	CSR_WRITE_4(sc, JME_STATCSR, 0xFFFFFFFF);
}