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
struct tmpfs_mount {scalar_t__ tm_pages_max; } ;

/* Variables and functions */
 scalar_t__ ULONG_MAX ; 
 size_t tmpfs_mem_avail () ; 
 scalar_t__ tmpfs_pages_used (struct tmpfs_mount*) ; 

__attribute__((used)) static size_t
tmpfs_pages_check_avail(struct tmpfs_mount *tmp, size_t req_pages)
{
	if (tmpfs_mem_avail() < req_pages)
		return (0);

	if (tmp->tm_pages_max != ULONG_MAX &&
	    tmp->tm_pages_max < req_pages + tmpfs_pages_used(tmp))
			return (0);

	return (1);
}