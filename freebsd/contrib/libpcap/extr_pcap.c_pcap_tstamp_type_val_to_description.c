#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int type; char const* description; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 TYPE_1__* tstamp_type_choices ; 

const char *
pcap_tstamp_type_val_to_description(int tstamp_type)
{
	int i;

	for (i = 0; tstamp_type_choices[i].name != NULL; i++) {
		if (tstamp_type_choices[i].type == tstamp_type)
			return (tstamp_type_choices[i].description);
	}
	return (NULL);
}