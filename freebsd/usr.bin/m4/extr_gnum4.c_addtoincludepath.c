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
struct path_entry {struct path_entry* next; } ;

/* Variables and functions */
 struct path_entry* first ; 
 struct path_entry* last ; 
 struct path_entry* new_path_entry (char const*) ; 

void
addtoincludepath(const char *dirname)
{
	struct path_entry *n;

	n = new_path_entry(dirname);

	if (last) {
		last->next = n;
		last = n;
	}
	else
		last = first = n;
}