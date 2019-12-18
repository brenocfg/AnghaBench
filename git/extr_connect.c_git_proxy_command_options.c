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
 int config_error_nonbool (char const*) ; 
 int git_default_config (char const*,char const*,void*) ; 
 scalar_t__ git_proxy_command ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 
 char* strstr (char const*,char*) ; 
 scalar_t__ xmemdupz (char const*,int) ; 

__attribute__((used)) static int git_proxy_command_options(const char *var, const char *value,
		void *cb)
{
	if (!strcmp(var, "core.gitproxy")) {
		const char *for_pos;
		int matchlen = -1;
		int hostlen;
		const char *rhost_name = cb;
		int rhost_len = strlen(rhost_name);

		if (git_proxy_command)
			return 0;
		if (!value)
			return config_error_nonbool(var);
		/* [core]
		 * ;# matches www.kernel.org as well
		 * gitproxy = netcatter-1 for kernel.org
		 * gitproxy = netcatter-2 for sample.xz
		 * gitproxy = netcatter-default
		 */
		for_pos = strstr(value, " for ");
		if (!for_pos)
			/* matches everybody */
			matchlen = strlen(value);
		else {
			hostlen = strlen(for_pos + 5);
			if (rhost_len < hostlen)
				matchlen = -1;
			else if (!strncmp(for_pos + 5,
					  rhost_name + rhost_len - hostlen,
					  hostlen) &&
				 ((rhost_len == hostlen) ||
				  rhost_name[rhost_len - hostlen -1] == '.'))
				matchlen = for_pos - value;
			else
				matchlen = -1;
		}
		if (0 <= matchlen) {
			/* core.gitproxy = none for kernel.org */
			if (matchlen == 4 &&
			    !memcmp(value, "none", 4))
				matchlen = 0;
			git_proxy_command = xmemdupz(value, matchlen);
		}
		return 0;
	}

	return git_default_config(var, value, cb);
}