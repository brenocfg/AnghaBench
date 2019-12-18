#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* end; struct TYPE_8__* start; int /*<<< orphan*/  pathlist; TYPE_1__* cb; } ;
typedef  TYPE_2__ git_iterator ;
struct TYPE_7__ {int /*<<< orphan*/  (* free ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_vector_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void git_iterator_free(git_iterator *iter)
{
	if (iter == NULL)
		return;

	iter->cb->free(iter);

	git_vector_free(&iter->pathlist);
	git__free(iter->start);
	git__free(iter->end);

	memset(iter, 0, sizeof(*iter));

	git__free(iter);
}