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
typedef  char u_char ;

/* Variables and functions */

__attribute__((used)) static int
nfsrv_cmpmixedcase(u_char *cp, u_char *cp2, int len)
{
	int i;
	u_char tmp;
	int fndlower = 0;

	for (i = 0; i < len; i++) {
		if (*cp >= 'A' && *cp <= 'Z') {
			tmp = *cp++ + ('a' - 'A');
		} else {
			tmp = *cp++;
			if (tmp >= 'a' && tmp <= 'z')
				fndlower = 1;
		}
		if (tmp != *cp2++)
			return (1);
	}
	if (fndlower)
		return (0);
	else
		return (1);
}