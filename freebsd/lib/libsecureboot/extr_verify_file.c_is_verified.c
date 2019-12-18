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
struct verify_status {scalar_t__ vs_dev; scalar_t__ vs_ino; int vs_status; struct verify_status* vs_next; } ;
struct stat {scalar_t__ st_dev; scalar_t__ st_ino; } ;

/* Variables and functions */
 int VE_NOT_CHECKED ; 
 struct verify_status* verified_files ; 

int
is_verified(struct stat *stp)
{
	struct verify_status *vsp;

	for (vsp = verified_files; vsp != NULL; vsp = vsp->vs_next) {
		if (stp->st_dev == vsp->vs_dev &&
		    stp->st_ino == vsp->vs_ino)
			return (vsp->vs_status);
	}
	return (VE_NOT_CHECKED);
}