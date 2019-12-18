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
struct archive_read {int /*<<< orphan*/  header_position; } ;
struct archive {int dummy; } ;
typedef  int /*<<< orphan*/  la_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_READ_MAGIC ; 
 int /*<<< orphan*/  ARCHIVE_STATE_ANY ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

la_int64_t
archive_read_header_position(struct archive *_a)
{
	struct archive_read *a = (struct archive_read *)_a;
	archive_check_magic(_a, ARCHIVE_READ_MAGIC,
	    ARCHIVE_STATE_ANY, "archive_read_header_position");
	return (a->header_position);
}