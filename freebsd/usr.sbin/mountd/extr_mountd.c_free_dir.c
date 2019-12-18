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
struct dirlist {struct dirlist* dp_dirp; int /*<<< orphan*/  dp_hosts; struct dirlist* dp_right; struct dirlist* dp_left; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct dirlist*) ; 
 int /*<<< orphan*/  free_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_dir(struct dirlist *dp)
{

	if (dp) {
		free_dir(dp->dp_left);
		free_dir(dp->dp_right);
		free_host(dp->dp_hosts);
		free(dp->dp_dirp);
		free(dp);
	}
}