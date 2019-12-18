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
struct TYPE_2__ {scalar_t__ ext_size; } ;
struct mbuf {int m_flags; TYPE_1__ m_ext; struct mbuf* m_next; } ;

/* Variables and functions */
 int MSIZE ; 
 int M_EXT ; 

__attribute__((used)) static int 
tcp_reass_overhead_of_chain(struct mbuf *m, struct mbuf **mlast)
{
	int len = MSIZE;

	if (m->m_flags & M_EXT)
		len += m->m_ext.ext_size;
	while (m->m_next != NULL) {
		m = m->m_next;
		len += MSIZE;
		if (m->m_flags & M_EXT)
			len += m->m_ext.ext_size;
	}
	*mlast = m;
	return (len);
}