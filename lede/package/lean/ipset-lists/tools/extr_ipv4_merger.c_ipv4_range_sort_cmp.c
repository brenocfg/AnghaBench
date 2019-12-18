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
struct ipv4_range {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */

__attribute__((used)) static int ipv4_range_sort_cmp(const void *a, const void *b)
{
	struct ipv4_range *ra = (struct ipv4_range *)a;
	struct ipv4_range *rb = (struct ipv4_range *)b;
	
	if (ra->start > rb->start) {
		return 1;
	} else if (ra->start < rb->start) {
		return -1;
	} else if (ra->end > rb->end) {
		return 1;
	} else if (ra->end < rb->end) {
		return -1;
	} else {
		return 0;
	}
}