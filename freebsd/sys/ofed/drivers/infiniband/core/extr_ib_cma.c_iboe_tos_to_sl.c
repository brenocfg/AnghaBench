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
struct net_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int iboe_tos_to_sl(struct net_device *ndev, int tos)
{
	/* get service level, SL, from IPv4 type of service, TOS */
	int sl = (tos >> 5) & 0x7;

	/* final mappings are done by the vendor specific drivers */
	return sl;
}