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
struct archive_write_filter {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_WARN ; 

__attribute__((used)) static int
archive_write_grzip_options(struct archive_write_filter *f, const char *key,
    const char *value)
{
	(void)f; /* UNUSED */
	(void)key; /* UNUSED */
	(void)value; /* UNUSED */
	/* Note: The "warn" return is just to inform the options
	 * supervisor that we didn't handle it.  It will generate
	 * a suitable error if no one used this option. */
	return (ARCHIVE_WARN);
}