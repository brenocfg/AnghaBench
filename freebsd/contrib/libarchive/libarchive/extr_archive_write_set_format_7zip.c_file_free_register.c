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
struct file {struct file* next; } ;
struct TYPE_2__ {struct file* first; } ;
struct _7zip {TYPE_1__ file_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  file_free (struct file*) ; 

__attribute__((used)) static void
file_free_register(struct _7zip *zip)
{
	struct file *file, *file_next;

	file = zip->file_list.first;
	while (file != NULL) {
		file_next = file->next;
		file_free(file);
		file = file_next;
	}
}