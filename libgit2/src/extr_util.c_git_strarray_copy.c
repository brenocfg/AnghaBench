#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t count; int /*<<< orphan*/ * strings; } ;
typedef  TYPE_1__ git_strarray ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * git__calloc (size_t,int) ; 
 int /*<<< orphan*/  git__strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int git_strarray_copy(git_strarray *tgt, const git_strarray *src)
{
	size_t i;

	assert(tgt && src);

	memset(tgt, 0, sizeof(*tgt));

	if (!src->count)
		return 0;

	tgt->strings = git__calloc(src->count, sizeof(char *));
	GIT_ERROR_CHECK_ALLOC(tgt->strings);

	for (i = 0; i < src->count; ++i) {
		if (!src->strings[i])
			continue;

		tgt->strings[tgt->count] = git__strdup(src->strings[i]);
		if (!tgt->strings[tgt->count]) {
			git_strarray_free(tgt);
			memset(tgt, 0, sizeof(*tgt));
			return -1;
		}

		tgt->count++;
	}

	return 0;
}