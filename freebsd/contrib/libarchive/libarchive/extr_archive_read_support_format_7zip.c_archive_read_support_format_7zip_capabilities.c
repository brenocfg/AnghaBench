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
 int ARCHIVE_READ_FORMAT_CAPS_ENCRYPT_DATA ; 
 int ARCHIVE_READ_FORMAT_CAPS_ENCRYPT_METADATA ; 

__attribute__((used)) static int
archive_read_support_format_7zip_capabilities(struct archive_read * a)
{
	(void)a; /* UNUSED */
	return (ARCHIVE_READ_FORMAT_CAPS_ENCRYPT_DATA |
			ARCHIVE_READ_FORMAT_CAPS_ENCRYPT_METADATA);
}