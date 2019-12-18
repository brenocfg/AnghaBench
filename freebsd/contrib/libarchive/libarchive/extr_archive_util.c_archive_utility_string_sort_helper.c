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
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  free (char**) ; 
 scalar_t__ realloc (char**,unsigned int) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
archive_utility_string_sort_helper(char **strings, unsigned int n)
{
	unsigned int i, lesser_count, greater_count;
	char **lesser, **greater, **tmp, *pivot;
	int retval1, retval2;

	/* A list of 0 or 1 elements is already sorted */
	if (n <= 1)
		return (ARCHIVE_OK);

	lesser_count = greater_count = 0;
	lesser = greater = NULL;
	pivot = strings[0];
	for (i = 1; i < n; i++)
	{
		if (strcmp(strings[i], pivot) < 0)
		{
			lesser_count++;
			tmp = (char **)realloc(lesser,
				lesser_count * sizeof(char *));
			if (!tmp) {
				free(greater);
				free(lesser);
				return (ARCHIVE_FATAL);
			}
			lesser = tmp;
			lesser[lesser_count - 1] = strings[i];
		}
		else
		{
			greater_count++;
			tmp = (char **)realloc(greater,
				greater_count * sizeof(char *));
			if (!tmp) {
				free(greater);
				free(lesser);
				return (ARCHIVE_FATAL);
			}
			greater = tmp;
			greater[greater_count - 1] = strings[i];
		}
	}

	/* quicksort(lesser) */
	retval1 = archive_utility_string_sort_helper(lesser, lesser_count);
	for (i = 0; i < lesser_count; i++)
		strings[i] = lesser[i];
	free(lesser);

	/* pivot */
	strings[lesser_count] = pivot;

	/* quicksort(greater) */
	retval2 = archive_utility_string_sort_helper(greater, greater_count);
	for (i = 0; i < greater_count; i++)
		strings[lesser_count + 1 + i] = greater[i];
	free(greater);

	return (retval1 < retval2) ? retval1 : retval2;
}