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
struct gpiod_lookup_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_add_lookup_table (struct gpiod_lookup_table*) ; 
 int /*<<< orphan*/  platform_device_register_simple (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sa11x0_register_pcmcia(int socket, struct gpiod_lookup_table *table)
{
	if (table)
		gpiod_add_lookup_table(table);
	platform_device_register_simple("sa11x0-pcmcia", socket, NULL, 0);
}