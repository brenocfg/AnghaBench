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
 int /*<<< orphan*/  AP_STA_CONNECTED ; 
 int /*<<< orphan*/  AP_STA_DISCONNECTED ; 
 int /*<<< orphan*/  cli_txt_list_add (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  cli_txt_list_del_addr (int /*<<< orphan*/ *,char const*) ; 
 char* os_strchr (char const*,char) ; 
 int /*<<< orphan*/  stations ; 
 scalar_t__ str_starts (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cli_event(const char *str)
{
	const char *start, *s;

	start = os_strchr(str, '>');
	if (start == NULL)
		return;

	start++;

	if (str_starts(start, AP_STA_CONNECTED)) {
		s = os_strchr(start, ' ');
		if (s == NULL)
			return;
		cli_txt_list_add(&stations, s + 1);
		return;
	}

	if (str_starts(start, AP_STA_DISCONNECTED)) {
		s = os_strchr(start, ' ');
		if (s == NULL)
			return;
		cli_txt_list_del_addr(&stations, s + 1);
		return;
	}
}