#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uma_zone_t ;
typedef  TYPE_2__* uma_keg_t ;
typedef  int /*<<< orphan*/  uma_init ;
typedef  int /*<<< orphan*/  uma_fini ;
typedef  int /*<<< orphan*/  uma_dtor ;
typedef  int /*<<< orphan*/  uma_ctor ;
struct uma_zctor_args {char* name; int flags; TYPE_2__* keg; int /*<<< orphan*/  align; int /*<<< orphan*/  fini; int /*<<< orphan*/  uminit; int /*<<< orphan*/  dtor; int /*<<< orphan*/  ctor; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_7__ {int uk_flags; int /*<<< orphan*/  uk_align; int /*<<< orphan*/  uk_size; } ;
struct TYPE_6__ {TYPE_2__* uz_keg; } ;

/* Variables and functions */
 scalar_t__ BOOT_BUCKETS ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  UMA_ANYDOMAIN ; 
 int UMA_ZONE_SECONDARY ; 
 scalar_t__ booted ; 
 int /*<<< orphan*/  memset (struct uma_zctor_args*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sx_slock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_reclaim_lock ; 
 TYPE_1__* zone_alloc_item (int /*<<< orphan*/ ,struct uma_zctor_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zones ; 

uma_zone_t
uma_zsecond_create(char *name, uma_ctor ctor, uma_dtor dtor,
		    uma_init zinit, uma_fini zfini, uma_zone_t master)
{
	struct uma_zctor_args args;
	uma_keg_t keg;
	uma_zone_t res;
	bool locked;

	keg = master->uz_keg;
	memset(&args, 0, sizeof(args));
	args.name = name;
	args.size = keg->uk_size;
	args.ctor = ctor;
	args.dtor = dtor;
	args.uminit = zinit;
	args.fini = zfini;
	args.align = keg->uk_align;
	args.flags = keg->uk_flags | UMA_ZONE_SECONDARY;
	args.keg = keg;

	if (booted < BOOT_BUCKETS) {
		locked = false;
	} else {
		sx_slock(&uma_reclaim_lock);
		locked = true;
	}
	/* XXX Attaches only one keg of potentially many. */
	res = zone_alloc_item(zones, &args, UMA_ANYDOMAIN, M_WAITOK);
	if (locked)
		sx_sunlock(&uma_reclaim_lock);
	return (res);
}