#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct thread {int dummy; } ;
struct proc {int dummy; } ;
struct ng_item {int dummy; } ;
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  NG_WORKLIST_LOCK_INIT () ; 
 int /*<<< orphan*/  RFHIGHPID ; 
 int /*<<< orphan*/  UMA_ALIGN_CACHE ; 
 int /*<<< orphan*/  kproc_kthread_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct proc**,struct thread**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  maxalloc ; 
 int /*<<< orphan*/  maxdata ; 
 int mp_ncpus ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_idhash_lock ; 
 int /*<<< orphan*/  ng_namehash_lock ; 
 int /*<<< orphan*/  ng_nodelist_mtx ; 
 int /*<<< orphan*/  ng_qdzone ; 
 int /*<<< orphan*/  ng_qzone ; 
 int /*<<< orphan*/  ng_topo_lock ; 
 int /*<<< orphan*/  ng_typelist_lock ; 
 int /*<<< orphan*/  ngq_mtx ; 
 int /*<<< orphan*/  ngthread ; 
 int numthreads ; 
 int /*<<< orphan*/  rw_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zone_set_max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ngb_mod_event(module_t mod, int event, void *data)
{
	struct proc *p;
	struct thread *td;
	int i, error = 0;

	switch (event) {
	case MOD_LOAD:
		/* Initialize everything. */
		NG_WORKLIST_LOCK_INIT();
		rw_init(&ng_typelist_lock, "netgraph types");
		rw_init(&ng_idhash_lock, "netgraph idhash");
		rw_init(&ng_namehash_lock, "netgraph namehash");
		rw_init(&ng_topo_lock, "netgraph topology mutex");
#ifdef	NETGRAPH_DEBUG
		mtx_init(&ng_nodelist_mtx, "netgraph nodelist mutex", NULL,
		    MTX_DEF);
		mtx_init(&ngq_mtx, "netgraph item list mutex", NULL,
		    MTX_DEF);
#endif
		ng_qzone = uma_zcreate("NetGraph items", sizeof(struct ng_item),
		    NULL, NULL, NULL, NULL, UMA_ALIGN_CACHE, 0);
		uma_zone_set_max(ng_qzone, maxalloc);
		ng_qdzone = uma_zcreate("NetGraph data items",
		    sizeof(struct ng_item), NULL, NULL, NULL, NULL,
		    UMA_ALIGN_CACHE, 0);
		uma_zone_set_max(ng_qdzone, maxdata);
		/* Autoconfigure number of threads. */
		if (numthreads <= 0)
			numthreads = mp_ncpus;
		/* Create threads. */
    		p = NULL; /* start with no process */
		for (i = 0; i < numthreads; i++) {
			if (kproc_kthread_add(ngthread, NULL, &p, &td,
			    RFHIGHPID, 0, "ng_queue", "ng_queue%d", i)) {
				numthreads = i;
				break;
			}
		}
		break;
	case MOD_UNLOAD:
		/* You can't unload it because an interface may be using it. */
		error = EBUSY;
		break;
	default:
		error = EOPNOTSUPP;
		break;
	}
	return (error);
}