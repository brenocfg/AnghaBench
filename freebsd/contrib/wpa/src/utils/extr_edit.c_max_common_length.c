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
 int common_len (char*,char*) ; 
 int os_strlen (char*) ; 

__attribute__((used)) static int max_common_length(char **c)
{
	int len, i;

	len = os_strlen(c[0]);
	for (i = 1; c[i]; i++) {
		int same = common_len(c[0], c[i]);
		if (same < len)
			len = same;
	}

	return len;
}