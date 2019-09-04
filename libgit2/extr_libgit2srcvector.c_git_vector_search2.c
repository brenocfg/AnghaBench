#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ (* git_vector_cmp ) (void const*,int /*<<< orphan*/ ) ;
struct TYPE_3__ {size_t length; int /*<<< orphan*/ * contents; } ;
typedef  TYPE_1__ git_vector ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  assert (int) ; 

int git_vector_search2(
	size_t *at_pos, const git_vector *v, git_vector_cmp key_lookup, const void *key)
{
	size_t i;

	assert(v && key && key_lookup);

	for (i = 0; i < v->length; ++i) {
		if (key_lookup(key, v->contents[i]) == 0) {
			if (at_pos)
				*at_pos = i;

			return 0;
		}
	}

	return GIT_ENOTFOUND;
}