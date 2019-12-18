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
typedef  unsigned int uintmax_t ;
struct archive_string {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_strappend_char (struct archive_string*,char const) ; 

__attribute__((used)) static void
append_uint(struct archive_string *as, uintmax_t d, unsigned base)
{
	static const char digits[] = "0123456789abcdef";
	if (d >= base)
		append_uint(as, d/base, base);
	archive_strappend_char(as, digits[d % base]);
}