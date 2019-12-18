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
struct TYPE_4__ {scalar_t__ ext_type; TYPE_1__* ext_pgs; } ;
struct mbuf {int m_flags; TYPE_2__ m_ext; } ;
struct TYPE_3__ {scalar_t__ nrdy; } ;

/* Variables and functions */
 scalar_t__ EXT_PGS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int M_EXT ; 
 struct mbuf* m_free (struct mbuf*) ; 

void
mb_free_notready(struct mbuf *m, int count)
{
	int i;

	for (i = 0; i < count && m != NULL; i++) {
		if ((m->m_flags & M_EXT) != 0 &&
		    m->m_ext.ext_type == EXT_PGS) {
			m->m_ext.ext_pgs->nrdy--;
			if (m->m_ext.ext_pgs->nrdy != 0)
				continue;
		}
		m = m_free(m);
	}
	KASSERT(i == count, ("Removed only %d items from %p", i, m));
}