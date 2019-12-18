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
typedef  int u8 ;

/* Variables and functions */
 scalar_t__ os_strcmp (char const*,char const*) ; 

__attribute__((used)) static int wpa_check_wowlan_trigger(const char *start, const char *trigger,
				    int capa_trigger, u8 *param_trigger)
{
	if (os_strcmp(start, trigger) != 0)
		return 0;
	if (!capa_trigger)
		return 0;

	*param_trigger = 1;
	return 1;
}