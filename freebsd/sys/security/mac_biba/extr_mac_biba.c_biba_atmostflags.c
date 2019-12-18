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
struct mac_biba {int mb_flags; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
biba_atmostflags(struct mac_biba *mb, int flags)
{

	if ((mb->mb_flags & flags) != mb->mb_flags)
		return (EINVAL);
	return (0);
}