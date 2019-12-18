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
struct TYPE_6__ {int refcount; int /*<<< orphan*/  linkmap; int /*<<< orphan*/  dl_refcount; int /*<<< orphan*/ * path; } ;
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  TYPE_1__ Obj_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  GDB_STATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_UTRACE (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RT_CONSISTENT ; 
 int /*<<< orphan*/  RT_DELETE ; 
 int /*<<< orphan*/  UTRACE_DLCLOSE_START ; 
 int /*<<< orphan*/  UTRACE_DLCLOSE_STOP ; 
 TYPE_1__* dlcheck (void*) ; 
 int /*<<< orphan*/  list_fini ; 
 int /*<<< orphan*/  objlist_call_fini (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unload_object (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unref_dag (TYPE_1__*) ; 

__attribute__((used)) static int
dlclose_locked(void *handle, RtldLockState *lockstate)
{
    Obj_Entry *root;

    root = dlcheck(handle);
    if (root == NULL)
	return -1;
    LD_UTRACE(UTRACE_DLCLOSE_START, handle, NULL, 0, root->dl_refcount,
	root->path);

    /* Unreference the object and its dependencies. */
    root->dl_refcount--;

    if (root->refcount == 1) {
	/*
	 * The object will be no longer referenced, so we must unload it.
	 * First, call the fini functions.
	 */
	objlist_call_fini(&list_fini, root, lockstate);

	unref_dag(root);

	/* Finish cleaning up the newly-unreferenced objects. */
	GDB_STATE(RT_DELETE,&root->linkmap);
	unload_object(root, lockstate);
	GDB_STATE(RT_CONSISTENT,NULL);
    } else
	unref_dag(root);

    LD_UTRACE(UTRACE_DLCLOSE_STOP, handle, NULL, 0, 0, NULL);
    return 0;
}