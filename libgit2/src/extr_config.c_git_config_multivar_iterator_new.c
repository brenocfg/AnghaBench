#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  next; int /*<<< orphan*/  free; } ;
struct TYPE_11__ {int have_regex; TYPE_1__ parent; TYPE_3__* iter; int /*<<< orphan*/  regex; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ multivar_iter ;
struct TYPE_12__ {int /*<<< orphan*/  (* free ) (TYPE_3__*) ;} ;
typedef  TYPE_3__ git_config_iterator ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 TYPE_2__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_2__*) ; 
 int git_config__normalize_name (char const*,int /*<<< orphan*/ *) ; 
 int git_config_iterator_new (TYPE_3__**,int /*<<< orphan*/  const*) ; 
 int git_regexp_compile (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multivar_iter_free ; 
 int /*<<< orphan*/  multivar_iter_next ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

int git_config_multivar_iterator_new(git_config_iterator **out, const git_config *cfg, const char *name, const char *regexp)
{
	multivar_iter *iter = NULL;
	git_config_iterator *inner = NULL;
	int error;

	if ((error = git_config_iterator_new(&inner, cfg)) < 0)
		return error;

	iter = git__calloc(1, sizeof(multivar_iter));
	GIT_ERROR_CHECK_ALLOC(iter);

	if ((error = git_config__normalize_name(name, &iter->name)) < 0)
		goto on_error;

	if (regexp != NULL) {
		if ((error = git_regexp_compile(&iter->regex, regexp, 0)) < 0)
			goto on_error;

		iter->have_regex = 1;
	}

	iter->iter = inner;
	iter->parent.free = multivar_iter_free;
	iter->parent.next = multivar_iter_next;

	*out = (git_config_iterator *) iter;

	return 0;

on_error:

	inner->free(inner);
	git__free(iter);
	return error;
}