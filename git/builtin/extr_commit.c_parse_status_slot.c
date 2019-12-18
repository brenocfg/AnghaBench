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
 int LOOKUP_CONFIG (int /*<<< orphan*/ ,char const*) ; 
 int WT_STATUS_UPDATED ; 
 int /*<<< orphan*/  color_status_slots ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

__attribute__((used)) static int parse_status_slot(const char *slot)
{
	if (!strcasecmp(slot, "added"))
		return WT_STATUS_UPDATED;

	return LOOKUP_CONFIG(color_status_slots, slot);
}