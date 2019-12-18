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
 int nmbclusters ; 
 int tcp_reass_maxseg ; 
 int /*<<< orphan*/  tcp_reass_zone ; 
 int uma_zone_set_max (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
tcp_reass_zone_change(void *tag)
{

	/* Set the zone limit and read back the effective value. */
	tcp_reass_maxseg = nmbclusters / 16;
	tcp_reass_maxseg = uma_zone_set_max(tcp_reass_zone,
	    tcp_reass_maxseg);
}