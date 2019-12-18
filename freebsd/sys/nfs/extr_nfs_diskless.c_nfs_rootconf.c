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

/* Variables and functions */
 scalar_t__ nfs_diskless_valid ; 
 int /*<<< orphan*/  nfs_setup_diskless () ; 
 char** rootdevnames ; 

__attribute__((used)) static void
nfs_rootconf(void)
{

	nfs_setup_diskless();
	if (nfs_diskless_valid)
		rootdevnames[0] = "nfs:";
}