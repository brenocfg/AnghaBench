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
typedef  int /*<<< orphan*/  enabler ;

/* Variables and functions */
 int /*<<< orphan*/  archive_read_disk_new ; 
 int /*<<< orphan*/  archive_read_free ; 
 int /*<<< orphan*/  archive_read_new ; 
 int /*<<< orphan*/  archive_write_disk_new ; 
 int /*<<< orphan*/  archive_write_free ; 
 int /*<<< orphan*/  archive_write_new ; 
 int /*<<< orphan*/  test_failure (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_success (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_filter_or_format(enabler enable)
{
	test_success(archive_read_new, enable, archive_read_free);
	test_failure(archive_write_new, enable, archive_write_free);
	test_failure(archive_read_disk_new, enable, archive_read_free);
	test_failure(archive_write_disk_new, enable, archive_write_free);
}