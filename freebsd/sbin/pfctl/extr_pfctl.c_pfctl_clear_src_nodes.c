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
 int /*<<< orphan*/  DIOCCLRSRCNODES ; 
 int PF_OPT_QUIET ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int
pfctl_clear_src_nodes(int dev, int opts)
{
	if (ioctl(dev, DIOCCLRSRCNODES))
		err(1, "DIOCCLRSRCNODES");
	if ((opts & PF_OPT_QUIET) == 0)
		fprintf(stderr, "source tracking entries cleared\n");
	return (0);
}