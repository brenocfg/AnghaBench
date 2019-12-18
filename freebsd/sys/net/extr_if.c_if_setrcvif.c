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
struct TYPE_2__ {int csum_flags; struct ifnet* rcvif; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ifnet {int dummy; } ;
typedef  scalar_t__ if_t ;

/* Variables and functions */
 int CSUM_SND_TAG ; 
 int /*<<< orphan*/  MPASS (int) ; 

void 
if_setrcvif(struct mbuf *m, if_t ifp)
{

	MPASS((m->m_pkthdr.csum_flags & CSUM_SND_TAG) == 0);
	m->m_pkthdr.rcvif = (struct ifnet *)ifp;
}