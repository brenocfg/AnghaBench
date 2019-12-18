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
struct archive_write {int dummy; } ;
typedef  size_t int64_t ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 size_t LOGICAL_BLOCK_SIZE ; 
 int write_null (struct archive_write*,size_t) ; 

__attribute__((used)) static int
wb_write_padding_to_temp(struct archive_write *a, int64_t csize)
{
	size_t ns;
	int ret;

	ns = (size_t)(csize % LOGICAL_BLOCK_SIZE);
	if (ns != 0)
		ret = write_null(a, LOGICAL_BLOCK_SIZE - ns);
	else
		ret = ARCHIVE_OK;
	return (ret);
}