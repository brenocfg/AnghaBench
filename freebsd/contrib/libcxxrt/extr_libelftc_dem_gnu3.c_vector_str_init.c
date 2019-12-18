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
struct vector_str {int capacity; int /*<<< orphan*/ * container; scalar_t__ size; } ;

/* Variables and functions */
 int VECTOR_DEF_CAPACITY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * malloc (int) ; 

__attribute__((used)) static bool
vector_str_init(struct vector_str *v)
{

	if (v == NULL)
		return (false);

	v->size = 0;
	v->capacity = VECTOR_DEF_CAPACITY;

	assert(v->capacity > 0);

	if ((v->container = malloc(sizeof(char *) * v->capacity)) == NULL)
		return (false);

	assert(v->container != NULL);

	return (true);
}