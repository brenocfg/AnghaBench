#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uma_slab_t ;
typedef  TYPE_2__* uma_keg_t ;
typedef  TYPE_3__* uma_domain_t ;
typedef  int uint8_t ;
struct TYPE_11__ {int /*<<< orphan*/  ud_full_slab; } ;
struct TYPE_10__ {int uk_rsize; TYPE_3__* uk_domain; int /*<<< orphan*/  uk_free; } ;
struct TYPE_9__ {scalar_t__ us_freecount; size_t us_domain; void* us_data; int /*<<< orphan*/  us_free; TYPE_2__* us_keg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_CLR (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int BIT_FFS (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEG_LOCK_ASSERT (TYPE_2__*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  SLAB_SETSIZE ; 
 int /*<<< orphan*/  us_link ; 

__attribute__((used)) static void *
slab_alloc_item(uma_keg_t keg, uma_slab_t slab)
{
	uma_domain_t dom;
	void *item;
	uint8_t freei;

	MPASS(keg == slab->us_keg);
	KEG_LOCK_ASSERT(keg);

	freei = BIT_FFS(SLAB_SETSIZE, &slab->us_free) - 1;
	BIT_CLR(SLAB_SETSIZE, freei, &slab->us_free);
	item = slab->us_data + (keg->uk_rsize * freei);
	slab->us_freecount--;
	keg->uk_free--;

	/* Move this slab to the full list */
	if (slab->us_freecount == 0) {
		LIST_REMOVE(slab, us_link);
		dom = &keg->uk_domain[slab->us_domain];
		LIST_INSERT_HEAD(&dom->ud_full_slab, slab, us_link);
	}

	return (item);
}