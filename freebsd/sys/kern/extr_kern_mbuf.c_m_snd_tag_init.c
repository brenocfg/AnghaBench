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
struct m_snd_tag {int /*<<< orphan*/  refcount; struct ifnet* ifp; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_ref (struct ifnet*) ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snd_tag_count ; 

void
m_snd_tag_init(struct m_snd_tag *mst, struct ifnet *ifp)
{

	if_ref(ifp);
	mst->ifp = ifp;
	refcount_init(&mst->refcount, 1);
	counter_u64_add(snd_tag_count, 1);
}