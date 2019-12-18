#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ qval; } ;
typedef  TYPE_1__ nfsquad_t ;

/* Variables and functions */
 int NFSCLIDVECSIZE ; 

__attribute__((used)) static int
nfsrv_fndclid(nfsquad_t *clidvec, nfsquad_t clid, int clidcnt)
{
	int i;

	/* If too many for the vector, return 1 since there might be a match. */
	if (clidcnt > NFSCLIDVECSIZE)
		return (1);

	for (i = 0; i < clidcnt; i++)
		if (clidvec[i].qval == clid.qval)
			return (1);
	return (0);
}