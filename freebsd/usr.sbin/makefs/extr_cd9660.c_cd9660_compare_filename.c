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
 int ISO_FILENAME_MAXLENGTH_BEFORE_VERSION ; 

__attribute__((used)) static int
cd9660_compare_filename(const char *first, const char *second)
{
	/*
	 * This can be made more optimal once it has been tested
	 * (the extra character, for example, is for testing)
	 */

	int p1 = 0;
	int p2 = 0;
	char c1, c2;
	/* First, on the filename */

	while (p1 < ISO_FILENAME_MAXLENGTH_BEFORE_VERSION-1
		&& p2 < ISO_FILENAME_MAXLENGTH_BEFORE_VERSION-1) {
		c1 = first[p1];
		c2 = second[p2];
		if (c1 == '.' && c2 =='.')
			break;
		else if (c1 == '.') {
			p2++;
			c1 = ' ';
		} else if (c2 == '.') {
			p1++;
			c2 = ' ';
		} else {
			p1++;
			p2++;
		}

		if (c1 < c2)
			return -1;
		else if (c1 > c2) {
			return 1;
		}
	}

	if (first[p1] == '.' && second[p2] == '.') {
		p1++;
		p2++;
		while (p1 < ISO_FILENAME_MAXLENGTH_BEFORE_VERSION - 1
			&& p2 < ISO_FILENAME_MAXLENGTH_BEFORE_VERSION - 1) {
			c1 = first[p1];
			c2 = second[p2];
			if (c1 == ';' && c2 == ';')
				break;
			else if (c1 == ';') {
				p2++;
				c1 = ' ';
			} else if (c2 == ';') {
				p1++;
				c2 = ' ';
			} else {
				p1++;
				p2++;
			}

			if (c1 < c2)
				return -1;
			else if (c1 > c2)
				return 1;
		}
	}
	return 0;
}