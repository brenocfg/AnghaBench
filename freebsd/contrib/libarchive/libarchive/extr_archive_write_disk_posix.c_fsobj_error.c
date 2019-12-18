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
 int /*<<< orphan*/  archive_string_sprintf (struct archive_string*,char*,char const*,char const*) ; 

__attribute__((used)) static void
fsobj_error(int *a_eno, struct archive_string *a_estr,
    int err, const char *errstr, const char *path)
{
	if (a_eno)
		*a_eno = err;
	if (a_estr)
		archive_string_sprintf(a_estr, "%s%s", errstr, path);
}