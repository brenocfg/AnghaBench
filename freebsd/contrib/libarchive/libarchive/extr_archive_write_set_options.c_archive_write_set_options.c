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
 int /*<<< orphan*/  ARCHIVE_WRITE_MAGIC ; 
 int _archive_set_options (struct archive*,char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_set_option ; 

int
archive_write_set_options(struct archive *a, const char *options)
{
	return _archive_set_options(a, options,
	    ARCHIVE_WRITE_MAGIC, "archive_write_set_options",
	    archive_set_option);
}