#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int mode_t ;
struct TYPE_3__ {int a_type; int a_perm; } ;
typedef  TYPE_1__ aclent_t ;

/* Variables and functions */
 int CLASS_OBJ ; 
 int EINVAL ; 
 int GROUP ; 
 int GROUP_OBJ ; 
 int USER ; 

__attribute__((used)) static int
ln_aent_preprocess(aclent_t *aclent, int n,
    int *hasmask, mode_t *mask,
    int *numuser, int *numgroup, int *needsort)
{
	int error = 0;
	int i;
	int curtype = 0;

	*hasmask = 0;
	*mask = 07;
	*needsort = 0;
	*numuser = 0;
	*numgroup = 0;

	for (i = 0; i < n; i++) {
		if (aclent[i].a_type < curtype)
			*needsort = 1;
		else if (aclent[i].a_type > curtype)
			curtype = aclent[i].a_type;
		if (aclent[i].a_type & USER)
			(*numuser)++;
		if (aclent[i].a_type & (GROUP | GROUP_OBJ))
			(*numgroup)++;
		if (aclent[i].a_type & CLASS_OBJ) {
			if (*hasmask) {
				error = EINVAL;
				goto out;
			} else {
				*hasmask = 1;
				*mask = aclent[i].a_perm;
			}
		}
	}

	if ((! *hasmask) && (*numuser + *numgroup > 1)) {
		error = EINVAL;
		goto out;
	}

out:
	return (error);
}