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
struct wpa_ssid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (char*,char const*,size_t) ; 
 size_t os_strlen (char const*) ; 
 int wpa_config_set (struct wpa_ssid*,char const*,char*,int /*<<< orphan*/ ) ; 

int wpa_config_set_quoted(struct wpa_ssid *ssid, const char *var,
			  const char *value)
{
	size_t len;
	char *buf;
	int ret;

	len = os_strlen(value);
	buf = os_malloc(len + 3);
	if (buf == NULL)
		return -1;
	buf[0] = '"';
	os_memcpy(buf + 1, value, len);
	buf[len + 1] = '"';
	buf[len + 2] = '\0';
	ret = wpa_config_set(ssid, var, buf, 0);
	os_free(buf);
	return ret;
}