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
struct rm_priotracker {int dummy; } ;
struct ktls_session {TYPE_1__* be; } ;
struct TYPE_2__ {int /*<<< orphan*/  use_count; } ;

/* Variables and functions */
 scalar_t__ ktls_allow_unload ; 
 int /*<<< orphan*/  ktls_backends_lock ; 
 int /*<<< orphan*/  ktls_cleanup (struct ktls_session*) ; 
 int /*<<< orphan*/  ktls_session_zone ; 
 int /*<<< orphan*/  rm_rlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 
 int /*<<< orphan*/  rm_runlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct ktls_session*) ; 

void
ktls_destroy(struct ktls_session *tls)
{
	struct rm_priotracker prio;

	ktls_cleanup(tls);
	if (tls->be != NULL && ktls_allow_unload) {
		rm_rlock(&ktls_backends_lock, &prio);
		tls->be->use_count--;
		rm_runlock(&ktls_backends_lock, &prio);
	}
	uma_zfree(ktls_session_zone, tls);
}