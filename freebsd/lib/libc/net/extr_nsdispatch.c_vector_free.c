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
typedef  int /*<<< orphan*/  (* vector_free_elem ) (void*) ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 void* vector_ref (unsigned int,void*,unsigned int,size_t) ; 

__attribute__((used)) static void
vector_free(void *vec, unsigned int *count, size_t esize,
    vector_free_elem free_elem)
{
	unsigned int	 i;
	void		*elem;

	for (i = 0; i < *count; i++) {
		elem = vector_ref(i, vec, *count, esize);
		if (elem != NULL)
			free_elem(elem);
	}
	free(vec);
	*count = 0;
}