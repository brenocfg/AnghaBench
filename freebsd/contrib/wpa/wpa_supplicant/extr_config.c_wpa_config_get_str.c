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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_config {int dummy; } ;

/* Variables and functions */
 int os_snprintf (char*,size_t,char*,char const*,...) ; 
 scalar_t__ os_snprintf_error (size_t,int) ; 

__attribute__((used)) static int wpa_config_get_str(const char *name, struct wpa_config *config,
			      long offset, char *buf, size_t buflen,
			      int pretty_print)
{
	char **val = (char **) (((u8 *) config) + (long) offset);
	int res;

	if (pretty_print)
		res = os_snprintf(buf, buflen, "%s=%s\n", name,
				  *val ? *val : "null");
	else if (!*val)
		return -1;
	else
		res = os_snprintf(buf, buflen, "%s", *val);
	if (os_snprintf_error(buflen, res))
		res = -1;

	return res;
}