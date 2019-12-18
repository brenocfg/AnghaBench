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
 int ARCHIVE_EOF ; 

__attribute__((used)) static int
archive_read_format_empty_read_data(struct archive_read *a,
    const void **buff, size_t *size, int64_t *offset)
{
	(void)a; /* UNUSED */
	(void)buff; /* UNUSED */
	(void)size; /* UNUSED */
	(void)offset; /* UNUSED */

	return (ARCHIVE_EOF);
}