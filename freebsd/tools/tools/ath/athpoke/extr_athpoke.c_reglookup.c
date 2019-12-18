#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dumpreg {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  ah_macRev; int /*<<< orphan*/  ah_macVersion; } ;
struct TYPE_4__ {int nregs; struct dumpreg** regs; TYPE_1__ revs; } ;
typedef  TYPE_1__ HAL_REVS ;

/* Variables and functions */
 scalar_t__ MAC_MATCH (struct dumpreg const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ state ; 
 scalar_t__ strcasecmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 

__attribute__((used)) static const struct dumpreg *
reglookup(const char *v)
{
	const HAL_REVS *revs = &state.revs;
	int i;

	if (strncasecmp(v, "AR_", 3) == 0)
		v += 3;
	for (i = 0; i < state.nregs; i++) {
		const struct dumpreg *dr = state.regs[i];
		if (MAC_MATCH(dr, revs->ah_macVersion, revs->ah_macRev) &&
		    strcasecmp(v, dr->name) == 0)
			return dr;
	}
	return NULL;
}