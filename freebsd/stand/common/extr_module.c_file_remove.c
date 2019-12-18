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
struct preloaded_file {struct preloaded_file* f_next; } ;

/* Variables and functions */
 struct preloaded_file* preloaded_files ; 

__attribute__((used)) static void
file_remove(struct preloaded_file *fp)
{
	struct preloaded_file   *cm;

	if (preloaded_files == NULL)
		return;

	if (preloaded_files == fp) {
		preloaded_files = fp->f_next;
		return;
        }
        for (cm = preloaded_files; cm->f_next != NULL; cm = cm->f_next) {
		if (cm->f_next == fp) {
			cm->f_next = fp->f_next;
			return;
		}
	}
}