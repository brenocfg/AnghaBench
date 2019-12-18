#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_11__ {int /*<<< orphan*/  loid; int /*<<< orphan*/  roid; TYPE_1__ refspec; } ;
typedef  TYPE_2__ push_spec ;
struct TYPE_12__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; struct TYPE_12__* dst_refname; struct TYPE_12__* src_refname; } ;
typedef  TYPE_3__ git_push_update ;
struct TYPE_13__ {int /*<<< orphan*/  updates; } ;
typedef  TYPE_4__ git_push ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_3__*) ; 
 TYPE_3__* git__calloc (int,int) ; 
 void* git__strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_vector_insert (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static int add_update(git_push *push, push_spec *spec)
{
	git_push_update *u = git__calloc(1, sizeof(git_push_update));
	GIT_ERROR_CHECK_ALLOC(u);

	u->src_refname = git__strdup(spec->refspec.src);
	GIT_ERROR_CHECK_ALLOC(u->src_refname);

	u->dst_refname = git__strdup(spec->refspec.dst);
	GIT_ERROR_CHECK_ALLOC(u->dst_refname);

	git_oid_cpy(&u->src, &spec->roid);
	git_oid_cpy(&u->dst, &spec->loid);

	return git_vector_insert(&push->updates, u);
}