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
struct mac_mls {int mm_flags; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
mls_atmostflags(struct mac_mls *mm, int flags)
{

	if ((mm->mm_flags & flags) != mm->mm_flags)
		return (EINVAL);
	return (0);
}