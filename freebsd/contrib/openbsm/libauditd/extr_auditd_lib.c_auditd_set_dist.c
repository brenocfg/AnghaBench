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
 int ADE_NOERR ; 
 int ADE_PARSE ; 
 int auditd_dist ; 
 int getacdist () ; 

int
auditd_set_dist(void)
{
	int ret;

	ret = getacdist();
	if (ret < 0)
		return (ADE_PARSE);

	auditd_dist = ret;

	return (ADE_NOERR);
}