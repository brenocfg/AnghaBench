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
 size_t INT_MAX ; 
 size_t SSIZE_MAX ; 
 scalar_t__ SV_CURPROC_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_ILP32 ; 
 scalar_t__ devfs_iosize_max_clamp ; 

size_t
devfs_iosize_max(void)
{

	return (devfs_iosize_max_clamp || SV_CURPROC_FLAG(SV_ILP32) ?
	    INT_MAX : SSIZE_MAX);
}