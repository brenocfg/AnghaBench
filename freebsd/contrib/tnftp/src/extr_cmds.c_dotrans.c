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
typedef  int ptrdiff_t ;

/* Variables and functions */
 char const* ntin ; 
 scalar_t__* ntout ; 

__attribute__((used)) static const char *
dotrans(char *dst, size_t dlen, const char *src)
{
	const char *cp1;
	char *cp2 = dst;
	size_t i, ostop;

	for (ostop = 0; *(ntout + ostop) && ostop < 16; ostop++)
		continue;
	for (cp1 = src; *cp1; cp1++) {
		int found = 0;
		for (i = 0; *(ntin + i) && i < 16; i++) {
			if (*cp1 == *(ntin + i)) {
				found++;
				if (i < ostop) {
					*cp2++ = *(ntout + i);
					if (cp2 - dst >= (ptrdiff_t)(dlen - 1))
						goto out;
				}
				break;
			}
		}
		if (!found) {
			*cp2++ = *cp1;
		}
	}
out:
	*cp2 = '\0';
	return dst;
}