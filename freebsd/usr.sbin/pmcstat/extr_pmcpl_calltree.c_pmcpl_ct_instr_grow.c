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
struct pmcpl_ct_instr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  PMCPL_CT_GROWSIZE ; 
 int /*<<< orphan*/  bzero (char*,unsigned int) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int max (int,int /*<<< orphan*/ ) ; 
 struct pmcpl_ct_instr* reallocarray (struct pmcpl_ct_instr*,unsigned int,int) ; 

__attribute__((used)) static void
pmcpl_ct_instr_grow(int cursize, int *maxsize, struct pmcpl_ct_instr **items)
{
	unsigned int nmaxsize;

	if (cursize < *maxsize)
		return;

	nmaxsize = *maxsize + max(cursize + 1 - *maxsize, PMCPL_CT_GROWSIZE);
	*items = reallocarray(*items, nmaxsize, sizeof(struct pmcpl_ct_instr));
	if (*items == NULL)
		errx(EX_SOFTWARE, "ERROR: out of memory");
	bzero((char *)*items + *maxsize * sizeof(struct pmcpl_ct_instr),
	    (nmaxsize - *maxsize) * sizeof(struct pmcpl_ct_instr));
	*maxsize = nmaxsize;
}