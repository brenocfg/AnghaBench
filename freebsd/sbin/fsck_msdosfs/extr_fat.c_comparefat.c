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
typedef  int /*<<< orphan*/  u_int ;
struct fatEntry {scalar_t__ next; } ;
struct bootblock {size_t NumClusters; } ;
typedef  size_t cl_t ;

/* Variables and functions */
 size_t CLUST_FIRST ; 
 int FSOK ; 
 int clustdiffer (size_t,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 

int
comparefat(struct bootblock *boot, struct fatEntry *first,
    struct fatEntry *second, u_int fatnum)
{
	cl_t cl;
	int ret = FSOK;

	for (cl = CLUST_FIRST; cl < boot->NumClusters; cl++)
		if (first[cl].next != second[cl].next)
			ret |= clustdiffer(cl, &first[cl].next, &second[cl].next, fatnum);
	return ret;
}