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
 scalar_t__ isalnum (int) ; 
 scalar_t__ isalpha (int) ; 
 scalar_t__ isupper (int) ; 
 int tolower (int) ; 

__attribute__((used)) static int token_eq(const char *s1, const char *s2)
{
	int c1;
	int c2;
	int end1 = 0;
	int end2 = 0;
	for (;;) {
		c1 = *s1++;
		c2 = *s2++;
		if (isalpha(c1) && isupper(c1))
			c1 = tolower(c1);
		if (isalpha(c2) && isupper(c2))
			c2 = tolower(c2);
		end1 = !(isalnum(c1) || c1 == '_' || c1 == '-');
		end2 = !(isalnum(c2) || c2 == '_' || c2 == '-');
		if (end1 || end2 || c1 != c2)
			break;
	}
	return end1 && end2; /* reached end of both words? */
}