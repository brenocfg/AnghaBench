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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_FAILED ; 
 int /*<<< orphan*/  archive_strappend_char (struct archive_string*,char const) ; 

__attribute__((used)) static ssize_t
extract_quotation(struct archive_string *as, const char *p)
{
	const char *s;

	for (s = p + 1; *s;) {
		if (*s == '\\') {
			if (s[1] != '\0') {
				archive_strappend_char(as, s[1]);
				s += 2;
			} else
				s++;
		} else if (*s == '"')
			break;
		else {
			archive_strappend_char(as, s[0]);
			s++;
		}
	}
	if (*s != '"')
		return (ARCHIVE_FAILED);/* Invalid sequence. */
	return ((ssize_t)(s + 1 - p));
}