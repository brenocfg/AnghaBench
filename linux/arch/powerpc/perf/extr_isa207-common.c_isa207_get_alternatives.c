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
typedef  int u64 ;

/* Variables and functions */
 int MAX_ALT ; 
 unsigned int PPMU_ONLY_COUNT_RUN ; 
 int find_alternative (int,unsigned int const**,int) ; 

int isa207_get_alternatives(u64 event, u64 alt[], int size, unsigned int flags,
					const unsigned int ev_alt[][MAX_ALT])
{
	int i, j, num_alt = 0;
	u64 alt_event;

	alt[num_alt++] = event;
	i = find_alternative(event, ev_alt, size);
	if (i >= 0) {
		/* Filter out the original event, it's already in alt[0] */
		for (j = 0; j < MAX_ALT; ++j) {
			alt_event = ev_alt[i][j];
			if (alt_event && alt_event != event)
				alt[num_alt++] = alt_event;
		}
	}

	if (flags & PPMU_ONLY_COUNT_RUN) {
		/*
		 * We're only counting in RUN state, so PM_CYC is equivalent to
		 * PM_RUN_CYC and PM_INST_CMPL === PM_RUN_INST_CMPL.
		 */
		j = num_alt;
		for (i = 0; i < num_alt; ++i) {
			switch (alt[i]) {
			case 0x1e:			/* PMC_CYC */
				alt[j++] = 0x600f4;	/* PM_RUN_CYC */
				break;
			case 0x600f4:
				alt[j++] = 0x1e;
				break;
			case 0x2:			/* PM_INST_CMPL */
				alt[j++] = 0x500fa;	/* PM_RUN_INST_CMPL */
				break;
			case 0x500fa:
				alt[j++] = 0x2;
				break;
			}
		}
		num_alt = j;
	}

	return num_alt;
}