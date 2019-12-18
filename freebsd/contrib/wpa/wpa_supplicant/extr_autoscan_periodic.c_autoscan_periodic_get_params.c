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
struct autoscan_periodic_data {int periodic_interval; } ;

/* Variables and functions */
 int atoi (char const*) ; 

__attribute__((used)) static int autoscan_periodic_get_params(struct autoscan_periodic_data *data,
					const char *params)
{
	int interval;

	if (params == NULL)
		return -1;

	interval = atoi(params);

	if (interval < 0)
		return -1;

	data->periodic_interval = interval;

	return 0;
}