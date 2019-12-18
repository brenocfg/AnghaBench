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
typedef  scalar_t__ uint32_t ;
struct cpsw_softc {int /*<<< orphan*/ * shadow_stats; } ;
struct TYPE_2__ {scalar_t__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPSW_DEBUGF (struct cpsw_softc*,char*) ; 
 scalar_t__ CPSW_STATS_OFFSET ; 
 int CPSW_SYSCTL_COUNT ; 
 scalar_t__ cpsw_read_4 (struct cpsw_softc*,scalar_t__) ; 
 TYPE_1__* cpsw_stat_sysctls ; 
 int /*<<< orphan*/  cpsw_write_4 (struct cpsw_softc*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
cpsw_stats_collect(struct cpsw_softc *sc)
{
	int i;
	uint32_t r;

	CPSW_DEBUGF(sc, ("Controller shadow statistics updated."));

	for (i = 0; i < CPSW_SYSCTL_COUNT; ++i) {
		r = cpsw_read_4(sc, CPSW_STATS_OFFSET +
		    cpsw_stat_sysctls[i].reg);
		sc->shadow_stats[i] += r;
		cpsw_write_4(sc, CPSW_STATS_OFFSET + cpsw_stat_sysctls[i].reg,
		    r);
	}
}