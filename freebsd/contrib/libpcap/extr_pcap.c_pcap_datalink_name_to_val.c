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
struct TYPE_2__ {int dlt; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 TYPE_1__* dlt_choices ; 
 scalar_t__ pcap_strcasecmp (int /*<<< orphan*/ *,char const*) ; 

int
pcap_datalink_name_to_val(const char *name)
{
	int i;

	for (i = 0; dlt_choices[i].name != NULL; i++) {
		if (pcap_strcasecmp(dlt_choices[i].name, name) == 0)
			return (dlt_choices[i].dlt);
	}
	return (-1);
}