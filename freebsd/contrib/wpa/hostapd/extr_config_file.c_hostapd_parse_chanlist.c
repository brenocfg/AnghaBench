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
struct hostapd_config {int /*<<< orphan*/  acs_ch_list; } ;

/* Variables and functions */
 scalar_t__ freq_range_list_parse (int /*<<< orphan*/ *,char*) ; 
 char* os_strchr (char*,char) ; 

__attribute__((used)) static int hostapd_parse_chanlist(struct hostapd_config *conf, char *val)
{
	char *pos;

	/* for backwards compatibility, translate ' ' in conf str to ',' */
	pos = val;
	while (pos) {
		pos = os_strchr(pos, ' ');
		if (pos)
			*pos++ = ',';
	}
	if (freq_range_list_parse(&conf->acs_ch_list, val))
		return -1;

	return 0;
}