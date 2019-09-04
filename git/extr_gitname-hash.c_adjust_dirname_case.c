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
struct index_state {int dummy; } ;
struct dir_entry {scalar_t__ name; } ;

/* Variables and functions */
 struct dir_entry* find_dir_entry (struct index_state*,char*,int) ; 
 int /*<<< orphan*/  lazy_init_name_hash (struct index_state*) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,int) ; 

void adjust_dirname_case(struct index_state *istate, char *name)
{
	const char *startPtr = name;
	const char *ptr = startPtr;

	lazy_init_name_hash(istate);
	while (*ptr) {
		while (*ptr && *ptr != '/')
			ptr++;

		if (*ptr == '/') {
			struct dir_entry *dir;

			dir = find_dir_entry(istate, name, ptr - name);
			if (dir) {
				memcpy((void *)startPtr, dir->name + (startPtr - name), ptr - startPtr);
				startPtr = ptr + 1;
			}
			ptr++;
		}
	}
}