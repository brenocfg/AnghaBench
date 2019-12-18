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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ ARCHIVE_FAILED ; 
 int /*<<< orphan*/  archive_strappend_char (struct archive_string*,char const) ; 
 int /*<<< orphan*/  archive_string_empty (struct archive_string*) ; 
 scalar_t__ extract_quotation (struct archive_string*,char const*) ; 

__attribute__((used)) static ssize_t
get_argument(struct archive_string *as, const char *p)
{
	const char *s = p;

	archive_string_empty(as);

	/* Skip beginning space characters. */
	while (*s != '\0' && *s == ' ')
		s++;
	/* Copy non-space characters. */
	while (*s != '\0' && *s != ' ') {
		if (*s == '\\') {
			if (s[1] != '\0') {
				archive_strappend_char(as, s[1]);
				s += 2;
			} else {
				s++;/* Ignore this character.*/
				break;
			}
		} else if (*s == '"') {
			ssize_t q = extract_quotation(as, s);
			if (q < 0)
				return (ARCHIVE_FAILED);/* Invalid sequence. */
			s += q;
		} else {
			archive_strappend_char(as, s[0]);
			s++;
		}
	}
	return ((ssize_t)(s - p));
}