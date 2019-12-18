#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int8_t ;
struct dumpreg {int type; int addr; } ;
struct ath_diag {size_t ad_in_size; int /*<<< orphan*/ * ad_in_data; } ;
typedef  int /*<<< orphan*/  r ;
typedef  int /*<<< orphan*/ * caddr_t ;
struct TYPE_5__ {int nregs; struct dumpreg** regs; int /*<<< orphan*/  revs; } ;
struct TYPE_4__ {int start; int end; } ;
typedef  int /*<<< orphan*/  HAL_REVS ;
typedef  TYPE_1__ HAL_REGRANGE ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ malloc (size_t) ; 
 scalar_t__ match (struct dumpreg const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 TYPE_2__ state ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
ath_hal_setupregs(struct ath_diag *atd, int what)
{
	const HAL_REVS *revs = &state.revs;
	HAL_REGRANGE r;
	size_t space = 0;
	u_int8_t *cp;
	int i, brun, erun;

	brun = erun = -1;
	for (i = 0; i < state.nregs; i++) {
		const struct dumpreg *dr = state.regs[i];
		if ((what & dr->type) && match(dr, revs)) {
			if (erun + 4 != dr->addr) {
				if (brun != -1)
					space += sizeof(HAL_REGRANGE);
				brun = erun = dr->addr;
			} else
				erun = dr->addr;
		}
	}
	space += sizeof(HAL_REGRANGE);

	atd->ad_in_data = (caddr_t) malloc(space);
	if (atd->ad_in_data == NULL) {
		fprintf(stderr, "Cannot malloc memory for registers!\n");
		exit(-1);
	}
	atd->ad_in_size = space;
	cp = (u_int8_t *) atd->ad_in_data;
	brun = erun = -1;
	for (i = 0; i < state.nregs; i++) {
		const struct dumpreg *dr = state.regs[i];
		if ((what & dr->type) && match(dr, revs)) {
			if (erun + 4 != dr->addr) {
				if (brun != -1) {
					r.start = brun, r.end = erun;
					memcpy(cp, &r, sizeof(r));
					cp += sizeof(r);
				}
				brun = erun = dr->addr;
			} else
				erun = dr->addr;
		}
	}
	if (brun != -1) {
		r.start = brun, r.end = erun;
		memcpy(cp, &r, sizeof(r));
		cp += sizeof(r);
	}
	return space / sizeof(uint32_t);
}