#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ refcount; scalar_t__ filtees_loaded; int /*<<< orphan*/  path; int /*<<< orphan*/  mapsize; int /*<<< orphan*/  mapbase; scalar_t__ marker; } ;
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  TYPE_1__ Obj_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  LD_UTRACE (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_BEFORE (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  UTRACE_UNLOAD_OBJECT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_marker (TYPE_1__*) ; 
 int /*<<< orphan*/  obj_count ; 
 int /*<<< orphan*/  obj_list ; 
 int /*<<< orphan*/  release_object (TYPE_1__*) ; 
 int /*<<< orphan*/  unlink_object (TYPE_1__*) ; 
 int /*<<< orphan*/  unload_filtees (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
unload_object(Obj_Entry *root, RtldLockState *lockstate)
{
	Obj_Entry marker, *obj, *next;

	assert(root->refcount == 0);

	/*
	 * Pass over the DAG removing unreferenced objects from
	 * appropriate lists.
	 */
	unlink_object(root);

	/* Unmap all objects that are no longer referenced. */
	for (obj = TAILQ_FIRST(&obj_list); obj != NULL; obj = next) {
		next = TAILQ_NEXT(obj, next);
		if (obj->marker || obj->refcount != 0)
			continue;
		LD_UTRACE(UTRACE_UNLOAD_OBJECT, obj, obj->mapbase,
		    obj->mapsize, 0, obj->path);
		dbg("unloading \"%s\"", obj->path);
		/*
		 * Unlink the object now to prevent new references from
		 * being acquired while the bind lock is dropped in
		 * recursive dlclose() invocations.
		 */
		TAILQ_REMOVE(&obj_list, obj, next);
		obj_count--;

		if (obj->filtees_loaded) {
			if (next != NULL) {
				init_marker(&marker);
				TAILQ_INSERT_BEFORE(next, &marker, next);
				unload_filtees(obj, lockstate);
				next = TAILQ_NEXT(&marker, next);
				TAILQ_REMOVE(&obj_list, &marker, next);
			} else
				unload_filtees(obj, lockstate);
		}
		release_object(obj);
	}
}