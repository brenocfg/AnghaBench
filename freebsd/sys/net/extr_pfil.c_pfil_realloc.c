#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mbuf {int dummy; } ;
struct ifnet {int dummy; } ;
struct TYPE_5__ {struct mbuf** m; int /*<<< orphan*/  mem; } ;
typedef  TYPE_1__ pfil_packet_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  PFIL_LENGTH (int) ; 
 int PFIL_MEMPTR ; 
 struct mbuf* m_devget (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifnet*,int /*<<< orphan*/ *) ; 
 TYPE_1__ pfil_packet_align (TYPE_1__) ; 

int
pfil_realloc(pfil_packet_t *p, int flags, struct ifnet *ifp)
{
	struct mbuf *m;

	MPASS(flags & PFIL_MEMPTR);

	if ((m = m_devget(p->mem, PFIL_LENGTH(flags), 0, ifp, NULL)) == NULL)
		return (ENOMEM);
	*p = pfil_packet_align(*p);
	*p->m = m;

	return (0);
}