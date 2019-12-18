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
struct sockaddr {int dummy; } ;
struct dirlist {struct dirlist* dp_right; struct dirlist* dp_left; } ;

/* Variables and functions */
 scalar_t__ chk_host (struct dirlist*,struct sockaddr*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
scan_tree(struct dirlist *dp, struct sockaddr *saddr)
{
	int defset, hostset;

	if (dp) {
		if (scan_tree(dp->dp_left, saddr))
			return (1);
		if (chk_host(dp, saddr, &defset, &hostset, NULL, NULL))
			return (1);
		if (scan_tree(dp->dp_right, saddr))
			return (1);
	}
	return (0);
}