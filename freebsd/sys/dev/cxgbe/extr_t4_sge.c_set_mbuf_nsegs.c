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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  l5hlen; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_ASSERTPKTHDR (struct mbuf*) ; 

__attribute__((used)) static inline void
set_mbuf_nsegs(struct mbuf *m, uint8_t nsegs)
{

	M_ASSERTPKTHDR(m);
	m->m_pkthdr.l5hlen = nsegs;
}