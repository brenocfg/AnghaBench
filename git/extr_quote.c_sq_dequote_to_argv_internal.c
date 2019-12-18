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
struct argv_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (char const**,int,int) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char*) ; 
 char* sq_dequote_step (char*,char**) ; 

__attribute__((used)) static int sq_dequote_to_argv_internal(char *arg,
				       const char ***argv, int *nr, int *alloc,
				       struct argv_array *array)
{
	char *next = arg;

	if (!*arg)
		return 0;
	do {
		char *dequoted = sq_dequote_step(next, &next);
		if (!dequoted)
			return -1;
		if (argv) {
			ALLOC_GROW(*argv, *nr + 1, *alloc);
			(*argv)[(*nr)++] = dequoted;
		}
		if (array)
			argv_array_push(array, dequoted);
	} while (next);

	return 0;
}