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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ BUS_GET_DOMAIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int printf (char*,int) ; 

int
bus_print_child_domain(device_t dev, device_t child)
{
	int domain;

	/* No domain? Don't print anything */
	if (BUS_GET_DOMAIN(dev, child, &domain) != 0)
		return (0);

	return (printf(" numa-domain %d", domain));
}