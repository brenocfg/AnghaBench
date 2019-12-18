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
 char* memchr (char const*,int,unsigned int) ; 
 scalar_t__ memcmp (char*,char const*,unsigned int) ; 
 unsigned int strlen (char const*) ; 

char *ath79_nvram_find_var(const char *name, const char *buf, unsigned buf_len)
{
	unsigned len = strlen(name);
	char *cur, *last;

	if (buf_len == 0 || len == 0)
		return NULL;

	if (buf_len < len)
		return NULL;

	if (len == 1)
		return memchr(buf, (int) *name, buf_len);

	last = (char *) buf + buf_len - len;
	for (cur = (char *) buf; cur <= last; cur++)
		if (cur[0] == name[0] && memcmp(cur, name, len) == 0)
			return cur + len;

	return NULL;
}