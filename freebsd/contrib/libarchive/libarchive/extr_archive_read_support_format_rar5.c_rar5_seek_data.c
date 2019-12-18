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
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_FATAL ; 

__attribute__((used)) static int64_t rar5_seek_data(struct archive_read *a, int64_t offset,
    int whence)
{
	(void) a;
	(void) offset;
	(void) whence;

	/* We're a streaming unpacker, and we don't support seeking. */

	return ARCHIVE_FATAL;
}