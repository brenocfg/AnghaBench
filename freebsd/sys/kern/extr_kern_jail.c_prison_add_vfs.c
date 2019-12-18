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
struct vfsconf {int /*<<< orphan*/  vfc_name; void* vfc_prison_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  asprintf (char**,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 void* prison_add_allow (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

void
prison_add_vfs(struct vfsconf *vfsp)
{
#ifdef NO_SYSCTL_DESCR

	vfsp->vfc_prison_flag = prison_add_allow("mount", vfsp->vfc_name,
	    NULL, NULL);
#else
	char *descr;

	(void)asprintf(&descr, M_TEMP, "Jail may mount the %s file system",
	    vfsp->vfc_name);
	vfsp->vfc_prison_flag = prison_add_allow("mount", vfsp->vfc_name,
	    NULL, descr);
	free(descr, M_TEMP);
#endif
}