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
 int /*<<< orphan*/  file_discard (struct preloaded_file*) ; 
 scalar_t__ loadaddr ; 
 struct preloaded_file* preloaded_files ; 
 int /*<<< orphan*/  unsetenv (char*) ; 

void
unload(void)
{
	struct preloaded_file *fp;

	while (preloaded_files != NULL) {
		fp = preloaded_files;
		preloaded_files = preloaded_files->f_next;
		file_discard(fp);
	}
	loadaddr = 0;
	unsetenv("kernelname");
}