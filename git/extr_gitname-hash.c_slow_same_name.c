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
 unsigned char toupper (unsigned char) ; 

__attribute__((used)) static int slow_same_name(const char *name1, int len1, const char *name2, int len2)
{
	if (len1 != len2)
		return 0;

	while (len1) {
		unsigned char c1 = *name1++;
		unsigned char c2 = *name2++;
		len1--;
		if (c1 != c2) {
			c1 = toupper(c1);
			c2 = toupper(c2);
			if (c1 != c2)
				return 0;
		}
	}
	return 1;
}