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
 int /*<<< orphan*/  archive_strappend_char (struct archive_string*,char const) ; 
 int /*<<< orphan*/  archive_strcat (struct archive_string*,char*) ; 
 int /*<<< orphan*/  archive_strncat (struct archive_string*,char const*,size_t) ; 
 size_t strcspn (char const*,char const*) ; 

__attribute__((used)) static void
shar_quote(struct archive_string *buf, const char *str, int in_shell)
{
	static const char meta[] = "\n \t'`\";&<>()|*?{}[]\\$!#^~";
	size_t len;

	while (*str != '\0') {
		if ((len = strcspn(str, meta)) != 0) {
			archive_strncat(buf, str, len);
			str += len;
		} else if (*str == '\n') {
			if (in_shell)
				archive_strcat(buf, "\"\n\"");
			else
				archive_strcat(buf, "\\n");
			++str;
		} else {
			archive_strappend_char(buf, '\\');
			archive_strappend_char(buf, *str);
			++str;
		}
	}
}