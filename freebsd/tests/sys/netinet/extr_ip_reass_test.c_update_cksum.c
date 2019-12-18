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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct ip {int /*<<< orphan*/  ip_sum; } ;

/* Variables and functions */
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
update_cksum(struct ip *ip)
{
	size_t i;
	uint32_t cksum;
	uint16_t *cksump;

	ip->ip_sum = 0;
	cksump = (uint16_t *)ip;
	for (cksum = 0, i = 0; i < sizeof(*ip) / sizeof(*cksump); cksump++, i++)
		cksum += ntohs(*cksump);
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum = ~(cksum + (cksum >> 16));
	ip->ip_sum = htons((uint16_t)cksum);
}