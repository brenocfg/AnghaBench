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
struct componentname {int cn_namelen; char* cn_nameptr; } ;

/* Variables and functions */

__attribute__((used)) static int
ext2_is_dot_entry(struct componentname *cnp)
{
	if (cnp->cn_namelen <= 2 && cnp->cn_nameptr[0] == '.' &&
	    (cnp->cn_nameptr[1] == '.' || cnp->cn_nameptr[1] == '\0'))
		return (1);
	return (0);
}