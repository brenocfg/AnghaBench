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
struct isofile {struct isofile* allnext; } ;
struct TYPE_2__ {struct isofile* first; } ;
struct iso9660 {TYPE_1__ all_file_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  isofile_free (struct isofile*) ; 

__attribute__((used)) static void
isofile_free_all_entries(struct iso9660 *iso9660)
{
	struct isofile *file, *file_next;

	file = iso9660->all_file_list.first;
	while (file != NULL) {
		file_next = file->allnext;
		isofile_free(file);
		file = file_next;
	}
}