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
typedef  int /*<<< orphan*/  uint32_t ;
struct dumpreg {int type; int addr; } ;
struct TYPE_2__ {int nregs; struct dumpreg** regs; int /*<<< orphan*/  revs; } ;
typedef  int /*<<< orphan*/  HAL_REVS ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DUMP_BASEBAND ; 
 int /*<<< orphan*/  ath_hal_dumprange (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  match (struct dumpreg const*,int /*<<< orphan*/  const*) ; 
 TYPE_1__ state ; 

__attribute__((used)) static void
ath_hal_dumpbb(FILE *fd, int what)
{
	const HAL_REVS *revs = &state.revs;
	int i, brun, erun;

	brun = erun = 0;
	for (i = 0; i < state.nregs; i++) {
		const struct dumpreg *dr = state.regs[i];
		if (!match(dr, revs))
			continue;
		if (dr->type & DUMP_BASEBAND) {
			if (brun == 0) {
				brun = erun = dr->addr;
			} else if (dr->addr == erun + sizeof(uint32_t)) {
				erun = dr->addr;
			} else {
				ath_hal_dumprange(fd, brun, erun);
				brun = erun = dr->addr;
			}
		} else {
			if (brun != 0)
				ath_hal_dumprange(fd, brun, erun);
			brun = erun = 0;
		}
	}
	if (brun != 0)
		ath_hal_dumprange(fd, brun, erun);
}