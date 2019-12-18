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
typedef  char uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 

__attribute__((used)) static int
remove_var(uint8_t *buf, int len, const char *var_name)
{
	int nremoved, i, name_len;

	nremoved = 0;
	name_len = strlen(var_name);
	while (len > 0) {
		i = strlen(buf) + 1;
		if (i == 1)
			break;
		if (strncmp(buf, var_name, name_len) == 0 && buf[name_len] == '=') {
			memmove(buf, buf + i, len - i);
			memset(buf + len - i, '\0', i);
			nremoved += 1;
			continue;
		}
		len -= i;
		buf += i;
	}
	return nremoved;
}