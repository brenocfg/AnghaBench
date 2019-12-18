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
typedef  int uint32_t ;
struct cpsw_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPSW_CPDMA_CPDMA_EOI_VECTOR ; 
 int /*<<< orphan*/  CPSW_DEBUGF (struct cpsw_softc*,char*) ; 
 int CPSW_WR_C_MISC_EVNT_PEND ; 
 int CPSW_WR_C_MISC_HOST_PEND ; 
 int CPSW_WR_C_MISC_MDIOLINK ; 
 int CPSW_WR_C_MISC_MDIOUSER ; 
 int /*<<< orphan*/  CPSW_WR_C_MISC_STAT (int /*<<< orphan*/ ) ; 
 int CPSW_WR_C_MISC_STAT_PEND ; 
 int /*<<< orphan*/  MDIOLINKINTMASKED ; 
 int /*<<< orphan*/  cpsw_intr_misc_host_error (struct cpsw_softc*) ; 
 int cpsw_read_4 (struct cpsw_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_stats_collect (struct cpsw_softc*) ; 
 int /*<<< orphan*/  cpsw_write_4 (struct cpsw_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cpsw_intr_misc(void *arg)
{
	struct cpsw_softc *sc = arg;
	uint32_t stat = cpsw_read_4(sc, CPSW_WR_C_MISC_STAT(0));

	if (stat & CPSW_WR_C_MISC_EVNT_PEND)
		CPSW_DEBUGF(sc, ("Time sync event interrupt unimplemented"));
	if (stat & CPSW_WR_C_MISC_STAT_PEND)
		cpsw_stats_collect(sc);
	if (stat & CPSW_WR_C_MISC_HOST_PEND)
		cpsw_intr_misc_host_error(sc);
	if (stat & CPSW_WR_C_MISC_MDIOLINK) {
		cpsw_write_4(sc, MDIOLINKINTMASKED,
		    cpsw_read_4(sc, MDIOLINKINTMASKED));
	}
	if (stat & CPSW_WR_C_MISC_MDIOUSER) {
		CPSW_DEBUGF(sc,
		    ("MDIO operation completed interrupt unimplemented"));
	}
	cpsw_write_4(sc, CPSW_CPDMA_CPDMA_EOI_VECTOR, 3);
}