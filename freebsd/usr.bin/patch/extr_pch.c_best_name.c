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
struct file_name {char* path; } ;

/* Variables and functions */
 size_t NEW_FILE ; 
 char* compare_names (struct file_name const*,int) ; 
 scalar_t__ ok_to_create_file ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static char *
best_name(const struct file_name *names, bool assume_exists)
{
	char *best;

	best = compare_names(names, assume_exists);

	/* No match?  Check to see if the diff could be creating a new file. */
	if (best == NULL && ok_to_create_file)
		best = names[NEW_FILE].path;

	return best ? xstrdup(best) : NULL;
}