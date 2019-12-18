#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * tqe_next; int /*<<< orphan*/ * tqe_prev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * tqe_next; int /*<<< orphan*/ * tqe_prev; } ;
struct pthread_mutex {TYPE_2__ m_pqe; TYPE_1__ m_qe; } ;

/* Variables and functions */

__attribute__((used)) static void
mutex_init_link(struct pthread_mutex *m)
{

#if defined(_PTHREADS_INVARIANTS)
	m->m_qe.tqe_prev = NULL;
	m->m_qe.tqe_next = NULL;
	m->m_pqe.tqe_prev = NULL;
	m->m_pqe.tqe_next = NULL;
#endif
}