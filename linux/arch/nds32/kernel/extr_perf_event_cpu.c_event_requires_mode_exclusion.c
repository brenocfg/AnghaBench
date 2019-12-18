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
struct perf_event_attr {scalar_t__ exclude_kernel; scalar_t__ exclude_user; } ;

/* Variables and functions */

__attribute__((used)) static int event_requires_mode_exclusion(struct perf_event_attr *attr)
{
	/* Other modes NDS32 does not support */
	return attr->exclude_user || attr->exclude_kernel;
}