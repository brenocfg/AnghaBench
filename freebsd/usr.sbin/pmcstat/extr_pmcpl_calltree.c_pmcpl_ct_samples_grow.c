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
struct pmcpl_ct_sample {unsigned int npmcs; int /*<<< orphan*/ * sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  PMCPL_CT_GROWSIZE ; 
 int /*<<< orphan*/  bzero (char*,unsigned int) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 unsigned int max (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int pmcstat_npmcs ; 
 int /*<<< orphan*/ * reallocarray (int /*<<< orphan*/ *,unsigned int,int) ; 

__attribute__((used)) static void
pmcpl_ct_samples_grow(struct pmcpl_ct_sample *samples)
{
	unsigned int npmcs;

	/* Enough storage. */
	if (pmcstat_npmcs <= samples->npmcs)
                return;

	npmcs = samples->npmcs +
	    max(pmcstat_npmcs - samples->npmcs, PMCPL_CT_GROWSIZE);
	samples->sb = reallocarray(samples->sb, npmcs, sizeof(unsigned));
	if (samples->sb == NULL)
		errx(EX_SOFTWARE, "ERROR: out of memory");
	bzero((char *)samples->sb + samples->npmcs * sizeof(unsigned),
	    (npmcs - samples->npmcs) * sizeof(unsigned));
	samples->npmcs = npmcs;
}