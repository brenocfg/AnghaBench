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
typedef  scalar_t__ git_vector_cmp ;
struct TYPE_5__ {scalar_t__ _cmp; int /*<<< orphan*/ * contents; scalar_t__ length; scalar_t__ _alloc_size; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_vector ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_MULTIPLY (size_t*,scalar_t__,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * git__malloc (size_t) ; 
 int /*<<< orphan*/  git_vector_set_sorted (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

int git_vector_dup(git_vector *v, const git_vector *src, git_vector_cmp cmp)
{
	assert(v && src);

	v->_alloc_size = 0;
	v->contents = NULL;
	v->_cmp = cmp ? cmp : src->_cmp;
	v->length = src->length;
	v->flags  = src->flags;
	if (cmp != src->_cmp)
		git_vector_set_sorted(v, 0);

	if (src->length) {
		size_t bytes;
		GIT_ERROR_CHECK_ALLOC_MULTIPLY(&bytes, src->length, sizeof(void *));
		v->contents = git__malloc(bytes);
		GIT_ERROR_CHECK_ALLOC(v->contents);
		v->_alloc_size = src->length;
		memcpy(v->contents, src->contents, bytes);
	}

	return 0;
}