#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t length; int /*<<< orphan*/ ** contents; } ;
typedef  TYPE_1__ git_vector ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_free (TYPE_1__*) ; 

void git_vector_free_deep(git_vector *v)
{
	size_t i;

	assert(v);

	for (i = 0; i < v->length; ++i) {
		git__free(v->contents[i]);
		v->contents[i] = NULL;
	}

	git_vector_free(v);
}