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
struct TYPE_3__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_4__ {int /*<<< orphan*/  flowid; TYPE_1__ PH_loc; } ;
struct mbuf {TYPE_2__ m_pkthdr; } ;
struct ifnet {int /*<<< orphan*/  if_index; int /*<<< orphan*/  if_vnet; } ;

/* Variables and functions */

__attribute__((used)) static __inline void
mld_save_context(struct mbuf *m, struct ifnet *ifp)
{

#ifdef VIMAGE
	m->m_pkthdr.PH_loc.ptr = ifp->if_vnet;
#endif /* VIMAGE */
	m->m_pkthdr.flowid = ifp->if_index;
}