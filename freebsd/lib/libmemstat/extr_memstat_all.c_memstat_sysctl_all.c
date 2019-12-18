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
struct memory_type_list {int dummy; } ;

/* Variables and functions */
 scalar_t__ memstat_sysctl_malloc (struct memory_type_list*,int) ; 
 scalar_t__ memstat_sysctl_uma (struct memory_type_list*,int) ; 

int
memstat_sysctl_all(struct memory_type_list *mtlp, int flags)
{

	if (memstat_sysctl_malloc(mtlp, flags) < 0)
		return (-1);
	if (memstat_sysctl_uma(mtlp, flags) < 0)
		return (-1);
	return (0);
}