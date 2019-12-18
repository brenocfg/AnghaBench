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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int NVSIDS ; 
 int VSID_NBPW ; 
 int /*<<< orphan*/  moea64_slb_mutex ; 
 int* moea64_vsid_bitmap ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
moea64_release_vsid(uint64_t vsid)
{
	int idx, mask;

	mtx_lock(&moea64_slb_mutex);
	idx = vsid & (NVSIDS-1);
	mask = 1 << (idx % VSID_NBPW);
	idx /= VSID_NBPW;
	KASSERT(moea64_vsid_bitmap[idx] & mask,
	    ("Freeing unallocated VSID %#jx", vsid));
	moea64_vsid_bitmap[idx] &= ~mask;
	mtx_unlock(&moea64_slb_mutex);
}