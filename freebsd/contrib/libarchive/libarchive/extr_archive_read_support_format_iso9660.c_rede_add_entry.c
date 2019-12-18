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
struct TYPE_2__ {struct file_info** last; } ;
struct file_info {struct file_info* re_next; TYPE_1__ rede_files; struct file_info* parent; int /*<<< orphan*/  re; } ;

/* Variables and functions */

__attribute__((used)) static inline int
rede_add_entry(struct file_info *file)
{
	struct file_info *re;

	/*
	 * Find "RE" entry.
	 */
	re = file->parent;
	while (re != NULL && !re->re)
		re = re->parent;
	if (re == NULL)
		return (-1);

	file->re_next = NULL;
	*re->rede_files.last = file;
	re->rede_files.last = &(file->re_next);
	return (0);
}