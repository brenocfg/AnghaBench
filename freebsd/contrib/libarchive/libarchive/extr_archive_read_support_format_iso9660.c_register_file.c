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
struct iso9660 {struct file_info* use_files; } ;
struct file_info {struct file_info* use_next; } ;

/* Variables and functions */

__attribute__((used)) static void
register_file(struct iso9660 *iso9660, struct file_info *file)
{

	file->use_next = iso9660->use_files;
	iso9660->use_files = file;
}