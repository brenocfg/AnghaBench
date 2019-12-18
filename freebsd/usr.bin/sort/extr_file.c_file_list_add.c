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
struct file_list {size_t count; size_t sz; char const** fns; } ;

/* Variables and functions */
 char const** sort_realloc (char const**,int) ; 
 char const* sort_strdup (char const*) ; 

void
file_list_add(struct file_list *fl, const char *fn, bool allocate)
{

	if (fl && fn) {
		if (fl->count >= fl->sz || (fl->fns == NULL)) {
			fl->sz = (fl->sz) * 2 + 1;
			fl->fns = sort_realloc(fl->fns, fl->sz *
			    sizeof(char *));
		}
		fl->fns[fl->count] = allocate ? sort_strdup(fn) : fn;
		fl->count += 1;
	}
}