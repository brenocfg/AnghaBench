#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_vector ;
struct TYPE_8__ {int push; } ;
typedef  TYPE_1__ git_refspec ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 TYPE_1__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_refspec__dispose (TYPE_1__*) ; 
 scalar_t__ git_refspec__parse (TYPE_1__*,char const*,int) ; 
 scalar_t__ git_vector_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int add_refspec_to(git_vector *vector, const char *string, bool is_fetch)
{
	git_refspec *spec;

	spec = git__calloc(1, sizeof(git_refspec));
	GIT_ERROR_CHECK_ALLOC(spec);

	if (git_refspec__parse(spec, string, is_fetch) < 0) {
		git__free(spec);
		return -1;
	}

	spec->push = !is_fetch;
	if (git_vector_insert(vector, spec) < 0) {
		git_refspec__dispose(spec);
		git__free(spec);
		return -1;
	}

	return 0;
}