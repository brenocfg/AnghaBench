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
typedef  int /*<<< orphan*/  tmp ;
struct archive_string {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_array_append (struct archive_string*,char const*,size_t) ; 
 int /*<<< orphan*/  archive_strappend_char (struct archive_string*,char) ; 
 int /*<<< orphan*/  archive_strcat (struct archive_string*,char const*) ; 
 char const* format_int (char*,int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
add_pax_attr_binary(struct archive_string *as, const char *key,
		    const char *value, size_t value_len)
{
	int digits, i, len, next_ten;
	char tmp[1 + 3 * sizeof(int)];	/* < 3 base-10 digits per byte */

	/*-
	 * PAX attributes have the following layout:
	 *     <len> <space> <key> <=> <value> <nl>
	 */
	len = 1 + (int)strlen(key) + 1 + (int)value_len + 1;

	/*
	 * The <len> field includes the length of the <len> field, so
	 * computing the correct length is tricky.  I start by
	 * counting the number of base-10 digits in 'len' and
	 * computing the next higher power of 10.
	 */
	next_ten = 1;
	digits = 0;
	i = len;
	while (i > 0) {
		i = i / 10;
		digits++;
		next_ten = next_ten * 10;
	}
	/*
	 * For example, if string without the length field is 99
	 * chars, then adding the 2 digit length "99" will force the
	 * total length past 100, requiring an extra digit.  The next
	 * statement adjusts for this effect.
	 */
	if (len + digits >= next_ten)
		digits++;

	/* Now, we have the right length so we can build the line. */
	tmp[sizeof(tmp) - 1] = 0;	/* Null-terminate the work area. */
	archive_strcat(as, format_int(tmp + sizeof(tmp) - 1, len + digits));
	archive_strappend_char(as, ' ');
	archive_strcat(as, key);
	archive_strappend_char(as, '=');
	archive_array_append(as, value, value_len);
	archive_strappend_char(as, '\n');
}