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

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  keep (char*) ; 
 char** kept ; 
 int kept_size ; 
 scalar_t__ string_in_use (char*) ; 

__attribute__((used)) static void
free_definition(char *ptr)
{
	int i;

	/* first try to free old strings */
	for (i = 0; i < kept_size; i++) {
		if (!string_in_use(kept[i])) {
			kept_size--;
			free(kept[i]);
			if (i != kept_size) 
				kept[i] = kept[kept_size];
			i--;
		}
	}

	/* then deal with us */
	if (string_in_use(ptr))
		keep(ptr);
	else
		free(ptr);
}