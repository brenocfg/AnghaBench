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
struct archive_read {int /*<<< orphan*/  filter; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  __archive_read_filter_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int64_t
__archive_read_seek(struct archive_read *a, int64_t offset, int whence)
{
	return __archive_read_filter_seek(a->filter, offset, whence);
}