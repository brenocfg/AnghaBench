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
typedef  int /*<<< orphan*/  Nlist ;
typedef  int /*<<< orphan*/ ** Hideset ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL ; 
 int HSSIZ ; 
 scalar_t__ domalloc (int) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ *** hidesets ; 
 int inserths (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int maxhidesets ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int nhidesets ; 
 scalar_t__ realloc (int /*<<< orphan*/ ***,int) ; 

int
newhideset(int hs, Nlist *np)
{
	int i, len;
	Nlist *nhs[HSSIZ+3];
	Hideset hs1, hs2;

	len = inserths(nhs, hidesets[hs], np);
	for (i=0; i<nhidesets; i++) {
		for (hs1=nhs, hs2=hidesets[i]; *hs1==*hs2; hs1++, hs2++)
			if (*hs1 == NULL)
				return i;
	}
	if (len>=HSSIZ)
		return hs;
	if (nhidesets >= maxhidesets) {
		maxhidesets = 3*maxhidesets/2+1;
		hidesets = (Hideset *)realloc(hidesets, (sizeof (Hideset *))*maxhidesets);
		if (hidesets == NULL)
			error(FATAL, "Out of memory from realloc");
	}
	hs1 = (Hideset)domalloc(len*sizeof(Hideset));
	memmove(hs1, nhs, len*sizeof(Hideset));
	hidesets[nhidesets] = hs1;
	return nhidesets++;
}