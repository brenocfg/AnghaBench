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
struct archive_string {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_strncat (struct archive_string*,char const*,int) ; 
 scalar_t__* safe_char ; 

__attribute__((used)) static void
mtree_quote(struct archive_string *s, const char *str)
{
	const char *start;
	char buf[4];
	unsigned char c;

	for (start = str; *str != '\0'; ++str) {
		if (safe_char[*(const unsigned char *)str])
			continue;
		if (start != str)
			archive_strncat(s, start, str - start);
		c = (unsigned char)*str;
		buf[0] = '\\';
		buf[1] = (c / 64) + '0';
		buf[2] = (c / 8 % 8) + '0';
		buf[3] = (c % 8) + '0';
		archive_strncat(s, buf, 4);
		start = str + 1;
	}

	if (start != str)
		archive_strncat(s, start, str - start);
}