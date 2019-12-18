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
struct group {char* gr_name; char* gr_passwd; scalar_t__ gr_gid; int /*<<< orphan*/ ** gr_mem; } ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 unsigned int GR_GID ; 
 unsigned int GR_MEM ; 
 unsigned int GR_NAME ; 
 unsigned int GR_PASSWD ; 

__attribute__((used)) static unsigned int
group_fields(const struct group *grp)
{
	unsigned int result;

	result = 0;

	if (grp->gr_name != NULL && grp->gr_name[0] != '\0')
		result |= GR_NAME;

	if (grp->gr_passwd != NULL && grp->gr_passwd[0] != '\0')
		result |= GR_PASSWD;

	if (grp->gr_gid != (gid_t)-1)
		result |= GR_GID;

	if (grp->gr_mem != NULL && grp->gr_mem[0] != NULL)
		result |= GR_MEM;

	return (result);
}