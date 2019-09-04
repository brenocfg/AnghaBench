#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  symbolic; } ;
struct TYPE_9__ {scalar_t__ type; int /*<<< orphan*/  db; int /*<<< orphan*/  peel; TYPE_1__ target; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ git_reference ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 int /*<<< orphan*/  GIT_REFCOUNT_INC (int /*<<< orphan*/ ) ; 
 scalar_t__ GIT_REFERENCE_SYMBOLIC ; 
 TYPE_2__* git_reference__alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* git_reference__alloc_symbolic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int git_reference_dup(git_reference **dest, git_reference *source)
{
	if (source->type == GIT_REFERENCE_SYMBOLIC)
		*dest = git_reference__alloc_symbolic(source->name, source->target.symbolic);
	else
		*dest = git_reference__alloc(source->name, &source->target.oid, &source->peel);

	GIT_ERROR_CHECK_ALLOC(*dest);

	(*dest)->db = source->db;
	GIT_REFCOUNT_INC((*dest)->db);

	return 0;
}