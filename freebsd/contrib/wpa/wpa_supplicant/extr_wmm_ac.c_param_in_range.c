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
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*,long,long,long) ; 

__attribute__((used)) static int param_in_range(const char *name, long value,
			  long min_val, long max_val)
{
	if (value < min_val || (max_val >= 0 && value > max_val)) {
		wpa_printf(MSG_DEBUG,
			   "WMM AC: param %s (%ld) is out of range (%ld-%ld)",
			   name, value, min_val, max_val);
		return 0;
	}

	return 1;
}