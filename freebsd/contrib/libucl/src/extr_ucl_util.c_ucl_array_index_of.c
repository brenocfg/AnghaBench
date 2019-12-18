#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ucl_object_t ;
struct TYPE_4__ {unsigned int n; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCL_ARRAY_GET (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kv_A (TYPE_1__,unsigned int) ; 
 TYPE_1__* vec ; 

unsigned int
ucl_array_index_of (ucl_object_t *top, ucl_object_t *elt)
{
	UCL_ARRAY_GET (vec, top);
	unsigned i;

	if (vec == NULL) {
		return (unsigned int)(-1);
	}

	for (i = 0; i < vec->n; i ++) {
		if (kv_A (*vec, i) == elt) {
			return i;
		}
	}

	return (unsigned int)(-1);
}