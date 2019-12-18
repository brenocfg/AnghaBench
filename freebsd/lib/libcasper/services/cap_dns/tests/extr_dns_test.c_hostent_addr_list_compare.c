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
 scalar_t__ memcmp (char*,char*,int) ; 

__attribute__((used)) static bool
hostent_addr_list_compare(char **addr_list0, char **addr_list1, int length)
{
	int i0, i1;

	if (addr_list0 == NULL && addr_list1 == NULL)
		return (true);
	if (addr_list0 == NULL || addr_list1 == NULL)
		return (false);

	for (i0 = 0; addr_list0[i0] != NULL; i0++) {
		for (i1 = 0; addr_list1[i1] != NULL; i1++) {
			if (memcmp(addr_list0[i0], addr_list1[i1], length) == 0)
				break;
		}
		if (addr_list1[i1] == NULL)
			return (false);
	}

	return (true);
}