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
struct rt_entry {int rt_state; } ;
struct khash {scalar_t__ k_gate; int k_state; scalar_t__ k_keep; } ;
typedef  scalar_t__ naddr ;
struct TYPE_2__ {scalar_t__ tv_sec; } ;

/* Variables and functions */
 int KS_CHECK ; 
 int KS_DELETE ; 
 int KS_DELETED ; 
 int KS_DYNAMIC ; 
 int KS_STATIC ; 
 scalar_t__ K_KEEP_LIM ; 
 int RS_STATIC ; 
 struct khash* kern_find (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__ now ; 
 int /*<<< orphan*/  rtbad (struct rt_entry*) ; 
 struct rt_entry* rtget (scalar_t__,scalar_t__) ; 

void
del_static(naddr dst,
	   naddr mask,
	   naddr gate,
	   int gone)
{
	struct khash *k;
	struct rt_entry *rt;

	/* Just mark it in the table to be deleted next time the kernel
	 * table is updated.
	 * If it has already been deleted, mark it as such, and set its
	 * keep-timer so that it will not be deleted again for a while.
	 * This lets the operator delete a route added by the daemon
	 * and add a replacement.
	 */
	k = kern_find(dst, mask, 0);
	if (k != NULL && (gate == 0 || k->k_gate == gate)) {
		k->k_state &= ~(KS_STATIC | KS_DYNAMIC | KS_CHECK);
		k->k_state |= KS_DELETE;
		if (gone) {
			k->k_state |= KS_DELETED;
			k->k_keep = now.tv_sec + K_KEEP_LIM;
		}
	}

	rt = rtget(dst, mask);
	if (rt != NULL && (rt->rt_state & RS_STATIC))
		rtbad(rt);
}