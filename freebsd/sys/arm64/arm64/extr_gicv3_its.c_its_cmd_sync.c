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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct its_cmd {int dummy; } ;
struct gicv3_its_softc {int sc_its_flags; } ;

/* Variables and functions */
 int ITS_FLAGS_CMDQ_FLUSH ; 
 int /*<<< orphan*/  cpu_dcache_wb_range (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dsb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ishst ; 

__attribute__((used)) static inline void
its_cmd_sync(struct gicv3_its_softc *sc, struct its_cmd *cmd)
{

	if ((sc->sc_its_flags & ITS_FLAGS_CMDQ_FLUSH) != 0) {
		/* Clean D-cache under command. */
		cpu_dcache_wb_range((vm_offset_t)cmd, sizeof(*cmd));
	} else {
		/* DSB inner shareable, store */
		dsb(ishst);
	}

}