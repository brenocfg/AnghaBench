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
 int /*<<< orphan*/  MSG_ERROR ; 
 int wpa_parse_cipher (char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int wpa_config_parse_cipher(int line, const char *value)
{
#ifdef CONFIG_NO_WPA
	return -1;
#else /* CONFIG_NO_WPA */
	int val = wpa_parse_cipher(value);
	if (val < 0) {
		wpa_printf(MSG_ERROR, "Line %d: invalid cipher '%s'.",
			   line, value);
		return -1;
	}
	if (val == 0) {
		wpa_printf(MSG_ERROR, "Line %d: no cipher values configured.",
			   line);
		return -1;
	}
	return val;
#endif /* CONFIG_NO_WPA */
}