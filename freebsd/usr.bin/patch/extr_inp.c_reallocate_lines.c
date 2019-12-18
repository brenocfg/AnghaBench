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
 int /*<<< orphan*/  free (char**) ; 
 char** i_ptr ; 
 int /*<<< orphan*/  i_size ; 
 int /*<<< orphan*/ * i_womp ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char** reallocarray (char**,size_t,int) ; 

__attribute__((used)) static bool
reallocate_lines(size_t *lines_allocated)
{
	char	**p;
	size_t	new_size;

	new_size = *lines_allocated * 3 / 2;
	p = reallocarray(i_ptr, new_size + 2, sizeof(char *));
	if (p == NULL) {	/* shucks, it was a near thing */
		munmap(i_womp, i_size);
		i_womp = NULL;
		free(i_ptr);
		i_ptr = NULL;
		*lines_allocated = 0;
		return false;
	}
	*lines_allocated = new_size;
	i_ptr = p;
	return true;
}