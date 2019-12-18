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
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  debug_level_str (int) ; 
 int /*<<< orphan*/  os_memcpy (char*,char*,int) ; 
 int os_snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 char* os_strchr (char*,char) ; 
 scalar_t__ os_strlen (char*) ; 
 int str_to_debug_level (char*) ; 
 int wpa_debug_level ; 
 int /*<<< orphan*/  wpa_debug_timestamp ; 

__attribute__((used)) static int hostapd_ctrl_iface_log_level(struct hostapd_data *hapd, char *cmd,
					char *buf, size_t buflen)
{
	char *pos, *end, *stamp;
	int ret;

	/* cmd: "LOG_LEVEL [<level>]" */
	if (*cmd == '\0') {
		pos = buf;
		end = buf + buflen;
		ret = os_snprintf(pos, end - pos, "Current level: %s\n"
				  "Timestamp: %d\n",
				  debug_level_str(wpa_debug_level),
				  wpa_debug_timestamp);
		if (os_snprintf_error(end - pos, ret))
			ret = 0;

		return ret;
	}

	while (*cmd == ' ')
		cmd++;

	stamp = os_strchr(cmd, ' ');
	if (stamp) {
		*stamp++ = '\0';
		while (*stamp == ' ') {
			stamp++;
		}
	}

	if (os_strlen(cmd)) {
		int level = str_to_debug_level(cmd);
		if (level < 0)
			return -1;
		wpa_debug_level = level;
	}

	if (stamp && os_strlen(stamp))
		wpa_debug_timestamp = atoi(stamp);

	os_memcpy(buf, "OK\n", 3);
	return 3;
}