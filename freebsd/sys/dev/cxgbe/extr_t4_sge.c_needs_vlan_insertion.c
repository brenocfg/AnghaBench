#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mbuf {int m_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_ASSERTPKTHDR (struct mbuf*) ; 
 int M_VLANTAG ; 

__attribute__((used)) static inline int
needs_vlan_insertion(struct mbuf *m)
{

	M_ASSERTPKTHDR(m);

	return (m->m_flags & M_VLANTAG);
}