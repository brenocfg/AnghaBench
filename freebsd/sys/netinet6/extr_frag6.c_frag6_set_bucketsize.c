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
 int IP6REASS_NHASH ; 
 int /*<<< orphan*/  V_ip6_maxfragbucketsize ; 
 int V_ip6_maxfragpackets ; 
 int /*<<< orphan*/  imax (int,int) ; 

__attribute__((used)) static void
frag6_set_bucketsize(void)
{
	int i;

	if ((i = V_ip6_maxfragpackets) > 0)
		V_ip6_maxfragbucketsize = imax(i / (IP6REASS_NHASH / 2), 1);
}