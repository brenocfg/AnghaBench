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
struct archive_read {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_WARN ; 

__attribute__((used)) static int rar5_options(struct archive_read *a, const char *key,
    const char *val) {
	(void) a;
	(void) key;
	(void) val;

	/* No options supported in this version. Return the ARCHIVE_WARN code
	 * to signal the options supervisor that the unpacker didn't handle
	 * setting this option. */

	return ARCHIVE_WARN;
}