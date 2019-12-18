#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int z_nodelete; int ref_nodel; int /*<<< orphan*/  linkmap; int /*<<< orphan*/  dl_refcount; int /*<<< orphan*/  path; int /*<<< orphan*/  dagmembers; scalar_t__ static_tls; int /*<<< orphan*/  refcount; } ;
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  int /*<<< orphan*/  Objlist ;
typedef  TYPE_1__ Obj_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  GDB_STATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_UTRACE (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int RTLD_GLOBAL ; 
 int RTLD_LO_DLOPEN ; 
 int RTLD_LO_EARLY ; 
 int RTLD_LO_NODELETE ; 
 int RTLD_LO_TRACE ; 
 int RTLD_MODEMASK ; 
 int RTLD_NOW ; 
 int /*<<< orphan*/  RT_ADD ; 
 int /*<<< orphan*/  RT_CONSISTENT ; 
 int /*<<< orphan*/  SYMLOOK_EARLY ; 
 int /*<<< orphan*/  TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UTRACE_DLOPEN_STOP ; 
 int /*<<< orphan*/  _rtld_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allocate_tls_offset (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  distribute_static_tls (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlopen_cleanup (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 TYPE_1__* globallist_curr (int /*<<< orphan*/ ) ; 
 TYPE_1__* globallist_next (TYPE_1__*) ; 
 int /*<<< orphan*/  init_dag (TYPE_1__*) ; 
 int /*<<< orphan*/  initlist_add_objects (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int initlist_objects_ifunc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ld_tracing ; 
 int /*<<< orphan*/  list_global ; 
 int load_needed_objects (TYPE_1__*,int) ; 
 TYPE_1__* load_object (char const*,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  lock_release (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_stacks_exec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obj_entry_q ; 
 int /*<<< orphan*/  obj_list ; 
 TYPE_1__* obj_main ; 
 int /*<<< orphan*/  obj_rtld ; 
 int /*<<< orphan*/  objlist_call_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  objlist_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * objlist_find (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  objlist_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  objlist_push_tail (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  process_z (TYPE_1__*) ; 
 int /*<<< orphan*/  ref_dag (TYPE_1__*) ; 
 int relocate_object_dag (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtld_bind_lock ; 
 int rtld_verify_versions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_loaded_objects (TYPE_1__*) ; 
 int /*<<< orphan*/  wlock_acquire (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Obj_Entry *
dlopen_object(const char *name, int fd, Obj_Entry *refobj, int lo_flags,
    int mode, RtldLockState *lockstate)
{
    Obj_Entry *old_obj_tail;
    Obj_Entry *obj;
    Objlist initlist;
    RtldLockState mlockstate;
    int result;

    objlist_init(&initlist);

    if (lockstate == NULL && !(lo_flags & RTLD_LO_EARLY)) {
	wlock_acquire(rtld_bind_lock, &mlockstate);
	lockstate = &mlockstate;
    }
    GDB_STATE(RT_ADD,NULL);

    old_obj_tail = globallist_curr(TAILQ_LAST(&obj_list, obj_entry_q));
    obj = NULL;
    if (name == NULL && fd == -1) {
	obj = obj_main;
	obj->refcount++;
    } else {
	obj = load_object(name, fd, refobj, lo_flags);
    }

    if (obj) {
	obj->dl_refcount++;
	if (mode & RTLD_GLOBAL && objlist_find(&list_global, obj) == NULL)
	    objlist_push_tail(&list_global, obj);
	if (globallist_next(old_obj_tail) != NULL) {
	    /* We loaded something new. */
	    assert(globallist_next(old_obj_tail) == obj);
	    result = 0;
	    if ((lo_flags & RTLD_LO_EARLY) == 0 && obj->static_tls &&
	      !allocate_tls_offset(obj)) {
		_rtld_error("%s: No space available "
		  "for static Thread Local Storage", obj->path);
		result = -1;
	    }
	    if (result != -1)
		result = load_needed_objects(obj, lo_flags & (RTLD_LO_DLOPEN |
		    RTLD_LO_EARLY));
	    init_dag(obj);
	    ref_dag(obj);
	    if (result != -1)
		result = rtld_verify_versions(&obj->dagmembers);
	    if (result != -1 && ld_tracing)
		goto trace;
	    if (result == -1 || relocate_object_dag(obj,
	      (mode & RTLD_MODEMASK) == RTLD_NOW, &obj_rtld,
	      (lo_flags & RTLD_LO_EARLY) ? SYMLOOK_EARLY : 0,
	      lockstate) == -1) {
		dlopen_cleanup(obj, lockstate);
		obj = NULL;
	    } else if (lo_flags & RTLD_LO_EARLY) {
		/*
		 * Do not call the init functions for early loaded
		 * filtees.  The image is still not initialized enough
		 * for them to work.
		 *
		 * Our object is found by the global object list and
		 * will be ordered among all init calls done right
		 * before transferring control to main.
		 */
	    } else {
		/* Make list of init functions to call. */
		initlist_add_objects(obj, obj, &initlist);
	    }
	    /*
	     * Process all no_delete or global objects here, given
	     * them own DAGs to prevent their dependencies from being
	     * unloaded.  This has to be done after we have loaded all
	     * of the dependencies, so that we do not miss any.
	     */
	    if (obj != NULL)
		process_z(obj);
	} else {
	    /*
	     * Bump the reference counts for objects on this DAG.  If
	     * this is the first dlopen() call for the object that was
	     * already loaded as a dependency, initialize the dag
	     * starting at it.
	     */
	    init_dag(obj);
	    ref_dag(obj);

	    if ((lo_flags & RTLD_LO_TRACE) != 0)
		goto trace;
	}
	if (obj != NULL && ((lo_flags & RTLD_LO_NODELETE) != 0 ||
	  obj->z_nodelete) && !obj->ref_nodel) {
	    dbg("obj %s nodelete", obj->path);
	    ref_dag(obj);
	    obj->z_nodelete = obj->ref_nodel = true;
	}
    }

    LD_UTRACE(UTRACE_DLOPEN_STOP, obj, NULL, 0, obj ? obj->dl_refcount : 0,
	name);
    GDB_STATE(RT_CONSISTENT,obj ? &obj->linkmap : NULL);

    if ((lo_flags & RTLD_LO_EARLY) == 0) {
	map_stacks_exec(lockstate);
	if (obj != NULL)
	    distribute_static_tls(&initlist, lockstate);
    }

    if (initlist_objects_ifunc(&initlist, (mode & RTLD_MODEMASK) == RTLD_NOW,
      (lo_flags & RTLD_LO_EARLY) ? SYMLOOK_EARLY : 0,
      lockstate) == -1) {
	objlist_clear(&initlist);
	dlopen_cleanup(obj, lockstate);
	if (lockstate == &mlockstate)
	    lock_release(rtld_bind_lock, lockstate);
	return (NULL);
    }

    if (!(lo_flags & RTLD_LO_EARLY)) {
	/* Call the init functions. */
	objlist_call_init(&initlist, lockstate);
    }
    objlist_clear(&initlist);
    if (lockstate == &mlockstate)
	lock_release(rtld_bind_lock, lockstate);
    return obj;
trace:
    trace_loaded_objects(obj);
    if (lockstate == &mlockstate)
	lock_release(rtld_bind_lock, lockstate);
    exit(0);
}