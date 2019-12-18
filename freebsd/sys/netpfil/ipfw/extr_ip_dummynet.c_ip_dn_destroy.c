#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  evheap; int /*<<< orphan*/  fshash; int /*<<< orphan*/  schedhash; } ;

/* Variables and functions */
 int /*<<< orphan*/  DN_BH_WLOCK () ; 
 int /*<<< orphan*/  DN_BH_WUNLOCK () ; 
 int /*<<< orphan*/  DN_LOCK_DESTROY () ; 
 int /*<<< orphan*/  ND (char*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 TYPE_1__ dn_cfg ; 
 int dn_gone ; 
 int /*<<< orphan*/  dn_ht_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_task ; 
 int /*<<< orphan*/  dn_timeout ; 
 int /*<<< orphan*/  dn_tq ; 
 int /*<<< orphan*/  dummynet_flush () ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ip_dn_ctl_ptr ; 
 int /*<<< orphan*/ * ip_dn_io_ptr ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ip_dn_destroy(int last)
{
	DN_BH_WLOCK();
	/* ensure no more callouts are started */
	dn_gone = 1;

	/* check for last */
	if (last) {
		ND("removing last instance\n");
		ip_dn_ctl_ptr = NULL;
		ip_dn_io_ptr = NULL;
	}

	dummynet_flush();
	DN_BH_WUNLOCK();

	callout_drain(&dn_timeout);
	taskqueue_drain(dn_tq, &dn_task);
	taskqueue_free(dn_tq);

	dn_ht_free(dn_cfg.schedhash, 0);
	dn_ht_free(dn_cfg.fshash, 0);
	heap_free(&dn_cfg.evheap);

	DN_LOCK_DESTROY();
}