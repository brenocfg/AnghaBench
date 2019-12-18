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
typedef  int u_int16_t ;
struct pf_frent {int fe_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTASSERT (int) ; 
 int PF_FRAG_ENTRY_POINTS ; 

__attribute__((used)) static inline int
pf_frent_index(struct pf_frent *frent)
{
	/*
	 * We have an array of 16 entry points to the queue.  A full size
	 * 65535 octet IP packet can have 8192 fragments.  So the queue
	 * traversal length is at most 512 and at most 16 entry points are
	 * checked.  We need 128 additional bytes on a 64 bit architecture.
	 */
	CTASSERT(((u_int16_t)0xffff &~ 7) / (0x10000 / PF_FRAG_ENTRY_POINTS) ==
	    16 - 1);
	CTASSERT(((u_int16_t)0xffff >> 3) / PF_FRAG_ENTRY_POINTS == 512 - 1);

	return frent->fe_off / (0x10000 / PF_FRAG_ENTRY_POINTS);
}