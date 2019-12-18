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
struct TYPE_2__ {struct file_info* first; struct file_info** last; } ;
struct file_info {TYPE_1__ rede_files; struct file_info* re_next; } ;

/* Variables and functions */

__attribute__((used)) static inline struct file_info *
rede_get_entry(struct file_info *re)
{
	struct file_info *file;

	if ((file = re->rede_files.first) != NULL) {
		re->rede_files.first = file->re_next;
		if (re->rede_files.first == NULL)
			re->rede_files.last =
			    &(re->rede_files.first);
	}
	return (file);
}