#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_3__ {int /*<<< orphan*/ * tcache; } ;
typedef  TYPE_1__ tcaches_t ;
typedef  int /*<<< orphan*/  tcache_t ;

/* Variables and functions */
 int /*<<< orphan*/ * TCACHES_ELM_NEED_REINIT ; 
 int /*<<< orphan*/  malloc_mutex_assert_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcaches_mtx ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static tcache_t *
tcaches_elm_remove(tsd_t *tsd, tcaches_t *elm, bool allow_reinit) {
	malloc_mutex_assert_owner(tsd_tsdn(tsd), &tcaches_mtx);

	if (elm->tcache == NULL) {
		return NULL;
	}
	tcache_t *tcache = elm->tcache;
	if (allow_reinit) {
		elm->tcache = TCACHES_ELM_NEED_REINIT;
	} else {
		elm->tcache = NULL;
	}

	if (tcache == TCACHES_ELM_NEED_REINIT) {
		return NULL;
	}
	return tcache;
}