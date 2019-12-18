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
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncasecmp (char const*,char const*,int) ; 

__attribute__((used)) static inline int at_mark(const char *string, int len,
			  const char **suffix, int nr)
{
	int i;

	for (i = 0; i < nr; i++) {
		int suffix_len = strlen(suffix[i]);
		if (suffix_len <= len
		    && !strncasecmp(string, suffix[i], suffix_len))
			return suffix_len;
	}
	return 0;
}