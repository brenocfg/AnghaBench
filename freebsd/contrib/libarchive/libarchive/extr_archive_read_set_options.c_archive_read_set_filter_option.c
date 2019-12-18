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
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_READ_MAGIC ; 
 int _archive_set_option (struct archive*,char const*,char const*,char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_set_filter_option ; 

int
archive_read_set_filter_option(struct archive *a, const char *m, const char *o,
    const char *v)
{
	return _archive_set_option(a, m, o, v,
	    ARCHIVE_READ_MAGIC, "archive_read_set_filter_option",
	    archive_set_filter_option);
}