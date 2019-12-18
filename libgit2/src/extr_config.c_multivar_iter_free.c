#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  regex; scalar_t__ have_regex; struct TYPE_4__* name; TYPE_2__* iter; } ;
typedef  TYPE_1__ multivar_iter ;
typedef  int /*<<< orphan*/  git_config_iterator ;
struct TYPE_5__ {int /*<<< orphan*/  (* free ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_regexp_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void multivar_iter_free(git_config_iterator *_iter)
{
	multivar_iter *iter = (multivar_iter *) _iter;

	iter->iter->free(iter->iter);

	git__free(iter->name);
	if (iter->have_regex)
		git_regexp_dispose(&iter->regex);
	git__free(iter);
}