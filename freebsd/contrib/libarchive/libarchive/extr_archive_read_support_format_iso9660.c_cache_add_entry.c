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
struct iso9660 {TYPE_1__ cache_files; } ;
struct file_info {struct file_info* next; } ;

/* Variables and functions */

__attribute__((used)) static inline void
cache_add_entry(struct iso9660 *iso9660, struct file_info *file)
{
	file->next = NULL;
	*iso9660->cache_files.last = file;
	iso9660->cache_files.last = &(file->next);
}