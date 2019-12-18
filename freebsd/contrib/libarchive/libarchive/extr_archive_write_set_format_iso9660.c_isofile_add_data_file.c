#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct isofile {struct isofile* datanext; } ;
struct TYPE_2__ {struct isofile** last; } ;
struct iso9660 {TYPE_1__ data_file_list; } ;

/* Variables and functions */

__attribute__((used)) static void
isofile_add_data_file(struct iso9660 *iso9660, struct isofile *file)
{
	file->datanext = NULL;
	*iso9660->data_file_list.last = file;
	iso9660->data_file_list.last = &(file->datanext);
}