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
typedef  int /*<<< orphan*/  uma_zone_t ;
typedef  int /*<<< orphan*/ * uma_init ;
typedef  int /*<<< orphan*/ * uma_fini ;
typedef  int /*<<< orphan*/ * uma_dtor ;
typedef  int /*<<< orphan*/ * uma_ctor ;
typedef  int uint32_t ;
struct uma_zctor_args {char const* name; size_t size; int align; int flags; int /*<<< orphan*/ * keg; int /*<<< orphan*/ * fini; int /*<<< orphan*/ * uminit; int /*<<< orphan*/ * dtor; int /*<<< orphan*/ * ctor; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 scalar_t__ BOOT_BUCKETS ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  UMA_ANYDOMAIN ; 
 int UMA_ZONE_NOFREE ; 
 int UMA_ZONE_NUMA ; 
 int UMA_ZONE_ZINIT ; 
 scalar_t__ booted ; 
 int /*<<< orphan*/  memset (struct uma_zctor_args*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  powerof2 (int) ; 
 int /*<<< orphan*/  sx_slock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * trash_ctor ; 
 int /*<<< orphan*/ * trash_dtor ; 
 int /*<<< orphan*/ * trash_fini ; 
 int /*<<< orphan*/ * trash_init ; 
 int /*<<< orphan*/  uma_reclaim_lock ; 
 int /*<<< orphan*/  zone_alloc_item (int /*<<< orphan*/ ,struct uma_zctor_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zones ; 

uma_zone_t
uma_zcreate(const char *name, size_t size, uma_ctor ctor, uma_dtor dtor,
		uma_init uminit, uma_fini fini, int align, uint32_t flags)

{
	struct uma_zctor_args args;
	uma_zone_t res;
	bool locked;

	KASSERT(powerof2(align + 1), ("invalid zone alignment %d for \"%s\"",
	    align, name));

	/* Sets all zones to a first-touch domain policy. */
#ifdef UMA_FIRSTTOUCH
	flags |= UMA_ZONE_NUMA;
#endif

	/* This stuff is essential for the zone ctor */
	memset(&args, 0, sizeof(args));
	args.name = name;
	args.size = size;
	args.ctor = ctor;
	args.dtor = dtor;
	args.uminit = uminit;
	args.fini = fini;
#ifdef  INVARIANTS
	/*
	 * If a zone is being created with an empty constructor and
	 * destructor, pass UMA constructor/destructor which checks for
	 * memory use after free.
	 */
	if ((!(flags & (UMA_ZONE_ZINIT | UMA_ZONE_NOFREE))) &&
	    ctor == NULL && dtor == NULL && uminit == NULL && fini == NULL) {
		args.ctor = trash_ctor;
		args.dtor = trash_dtor;
		args.uminit = trash_init;
		args.fini = trash_fini;
	}
#endif
	args.align = align;
	args.flags = flags;
	args.keg = NULL;

	if (booted < BOOT_BUCKETS) {
		locked = false;
	} else {
		sx_slock(&uma_reclaim_lock);
		locked = true;
	}
	res = zone_alloc_item(zones, &args, UMA_ANYDOMAIN, M_WAITOK);
	if (locked)
		sx_sunlock(&uma_reclaim_lock);
	return (res);
}