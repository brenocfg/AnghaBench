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
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int printf (char*,char*) ; 

int
bus_print_child_footer(device_t dev, device_t child)
{
	return (printf(" on %s\n", device_get_nameunit(dev)));
}