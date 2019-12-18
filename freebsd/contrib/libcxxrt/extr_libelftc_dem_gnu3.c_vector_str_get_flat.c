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
struct vector_str {size_t size; int /*<<< orphan*/ * container; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int get_strlen_sum (struct vector_str const*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
vector_str_get_flat(const struct vector_str *v, size_t *l)
{
	ssize_t elem_pos, elem_size, rtn_size;
	size_t i;
	char *rtn;

	if (v == NULL || v->size == 0)
		return (NULL);

	if ((rtn_size = get_strlen_sum(v)) == 0)
		return (NULL);

	if ((rtn = malloc(sizeof(char) * (rtn_size + 1))) == NULL)
		return (NULL);

	elem_pos = 0;
	for (i = 0; i < v->size; ++i) {
		elem_size = strlen(v->container[i]);

		memcpy(rtn + elem_pos, v->container[i], elem_size);

		elem_pos += elem_size;
	}

	rtn[rtn_size] = '\0';

	if (l != NULL)
		*l = rtn_size;

	return (rtn);
}