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
struct pt_last_ip {unsigned long long ip; scalar_t__ suppressed; scalar_t__ have_ip; } ;

/* Variables and functions */

void pt_last_ip_init(struct pt_last_ip *last_ip)
{
	if (!last_ip)
		return;

	last_ip->ip = 0ull;
	last_ip->have_ip = 0;
	last_ip->suppressed = 0;
}