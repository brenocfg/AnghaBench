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
typedef  int /*<<< orphan*/  wchar_t ;
struct archive_string {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  errno ; 

int
archive_string_append_from_wcs(struct archive_string *as,
    const wchar_t *w, size_t len)
{
	(void)as;/* UNUSED */
	(void)w;/* UNUSED */
	(void)len;/* UNUSED */
	errno = ENOSYS;
	return (-1);
}