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
struct archive_write_disk {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  write_data_block (struct archive_write_disk*,char const*,size_t) ; 

__attribute__((used)) static ssize_t
hfs_write_data_block(struct archive_write_disk *a, const char *buff,
    size_t size)
{
	return (write_data_block(a, buff, size));
}