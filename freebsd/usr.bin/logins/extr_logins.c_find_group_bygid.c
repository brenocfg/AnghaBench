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
struct xgroup {scalar_t__ gr_gid; } ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 struct xgroup* grps ; 
 unsigned int ngrps ; 

__attribute__((used)) static struct xgroup *
find_group_bygid(gid_t gid)
{
	unsigned int i;

	for (i = 0; i < ngrps; ++i)
		if (grps[i].gr_gid == gid)
			return (&grps[i]);
	return (NULL);
}