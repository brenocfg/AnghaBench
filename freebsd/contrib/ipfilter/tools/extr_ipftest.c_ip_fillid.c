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
typedef  int /*<<< orphan*/  uint16_t ;
struct ip {scalar_t__ ip_id; } ;

/* Variables and functions */

void
ip_fillid(struct ip *ip)
{
	static uint16_t ip_id;

	ip->ip_id = ip_id++;
}