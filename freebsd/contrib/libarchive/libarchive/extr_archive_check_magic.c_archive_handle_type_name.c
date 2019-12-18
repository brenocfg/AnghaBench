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

/* Variables and functions */
#define  ARCHIVE_MATCH_MAGIC 132 
#define  ARCHIVE_READ_DISK_MAGIC 131 
#define  ARCHIVE_READ_MAGIC 130 
#define  ARCHIVE_WRITE_DISK_MAGIC 129 
#define  ARCHIVE_WRITE_MAGIC 128 

__attribute__((used)) static const char *
archive_handle_type_name(unsigned m)
{
	switch (m) {
	case ARCHIVE_WRITE_MAGIC:	return ("archive_write");
	case ARCHIVE_READ_MAGIC:	return ("archive_read");
	case ARCHIVE_WRITE_DISK_MAGIC:	return ("archive_write_disk");
	case ARCHIVE_READ_DISK_MAGIC:	return ("archive_read_disk");
	case ARCHIVE_MATCH_MAGIC:	return ("archive_match");
	default:			return NULL;
	}
}