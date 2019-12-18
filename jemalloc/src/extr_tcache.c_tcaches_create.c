#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_4__ {int /*<<< orphan*/ * tcache; struct TYPE_4__* next; } ;
typedef  TYPE_1__ tcaches_t ;
typedef  int /*<<< orphan*/  tcache_t ;

/* Variables and functions */
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tcache_create_explicit (int /*<<< orphan*/ *) ; 
 TYPE_1__* tcaches ; 
 TYPE_1__* tcaches_avail ; 
 scalar_t__ tcaches_create_prep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcaches_mtx ; 
 size_t tcaches_past ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsdn_witness_tsdp_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  witness_assert_depth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
tcaches_create(tsd_t *tsd, unsigned *r_ind) {
	witness_assert_depth(tsdn_witness_tsdp_get(tsd_tsdn(tsd)), 0);

	bool err;

	if (tcaches_create_prep(tsd)) {
		err = true;
		goto label_return;
	}

	tcache_t *tcache = tcache_create_explicit(tsd);
	if (tcache == NULL) {
		err = true;
		goto label_return;
	}

	tcaches_t *elm;
	malloc_mutex_lock(tsd_tsdn(tsd), &tcaches_mtx);
	if (tcaches_avail != NULL) {
		elm = tcaches_avail;
		tcaches_avail = tcaches_avail->next;
		elm->tcache = tcache;
		*r_ind = (unsigned)(elm - tcaches);
	} else {
		elm = &tcaches[tcaches_past];
		elm->tcache = tcache;
		*r_ind = tcaches_past;
		tcaches_past++;
	}
	malloc_mutex_unlock(tsd_tsdn(tsd), &tcaches_mtx);

	err = false;
label_return:
	witness_assert_depth(tsdn_witness_tsdp_get(tsd_tsdn(tsd)), 0);
	return err;
}