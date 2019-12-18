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
struct ipv4_range {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void ipv4_range_swap(void *a, void *b, int size)
{
	struct ipv4_range *ra = (struct ipv4_range *)a;
	struct ipv4_range *rb = (struct ipv4_range *)b;
	struct ipv4_range tmp;
	tmp = *ra;
	*ra = *rb;
	*rb = tmp;
}