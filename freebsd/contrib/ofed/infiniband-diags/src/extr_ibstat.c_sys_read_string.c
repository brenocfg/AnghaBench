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
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int ret_code () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 
 char* strrchr (char*,char) ; 
 int sysctlbyname (char*,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int sys_read_string(const char *dir_name, const char *file_name, char *str, int max_len)
{
	char path[256], *s;
	size_t len;

	snprintf(path, sizeof(path), "%s/%s", dir_name, file_name);

	for (s = &path[0]; *s != '\0'; s++)
		if (*s == '/')
			*s = '.';

	len = max_len;
	if (sysctlbyname(&path[1], str, &len, NULL, 0) == -1)
		return ret_code();

	str[(len < max_len) ? len : max_len - 1] = 0;

	if ((s = strrchr(str, '\n')))
		*s = 0;

	return 0;
}