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
 int PUSH_COLOR_ERROR ; 
 int PUSH_COLOR_RESET ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

__attribute__((used)) static int parse_push_color_slot(const char *slot)
{
	if (!strcasecmp(slot, "reset"))
		return PUSH_COLOR_RESET;
	if (!strcasecmp(slot, "error"))
		return PUSH_COLOR_ERROR;
	return -1;
}