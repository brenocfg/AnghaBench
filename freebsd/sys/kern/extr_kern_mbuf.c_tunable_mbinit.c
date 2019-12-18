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
typedef  int quad_t ;

/* Variables and functions */
 int MCLBYTES ; 
 int MJUM16BYTES ; 
 int MJUM9BYTES ; 
 int MJUMPAGESIZE ; 
 int MSIZE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int /*<<< orphan*/  TUNABLE_QUAD_FETCH (char*,int*) ; 
 int lmax (int,int) ; 
 int maxmbufmem ; 
 int nmbclusters ; 
 int nmbjumbo16 ; 
 int nmbjumbo9 ; 
 int nmbjumbop ; 
 int nmbufs ; 
 scalar_t__ physmem ; 
 int qmin (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_kmem_size ; 

__attribute__((used)) static void
tunable_mbinit(void *dummy)
{
	quad_t realmem;

	/*
	 * The default limit for all mbuf related memory is 1/2 of all
	 * available kernel memory (physical or kmem).
	 * At most it can be 3/4 of available kernel memory.
	 */
	realmem = qmin((quad_t)physmem * PAGE_SIZE, vm_kmem_size);
	maxmbufmem = realmem / 2;
	TUNABLE_QUAD_FETCH("kern.ipc.maxmbufmem", &maxmbufmem);
	if (maxmbufmem > realmem / 4 * 3)
		maxmbufmem = realmem / 4 * 3;

	TUNABLE_INT_FETCH("kern.ipc.nmbclusters", &nmbclusters);
	if (nmbclusters == 0)
		nmbclusters = maxmbufmem / MCLBYTES / 4;

	TUNABLE_INT_FETCH("kern.ipc.nmbjumbop", &nmbjumbop);
	if (nmbjumbop == 0)
		nmbjumbop = maxmbufmem / MJUMPAGESIZE / 4;

	TUNABLE_INT_FETCH("kern.ipc.nmbjumbo9", &nmbjumbo9);
	if (nmbjumbo9 == 0)
		nmbjumbo9 = maxmbufmem / MJUM9BYTES / 6;

	TUNABLE_INT_FETCH("kern.ipc.nmbjumbo16", &nmbjumbo16);
	if (nmbjumbo16 == 0)
		nmbjumbo16 = maxmbufmem / MJUM16BYTES / 6;

	/*
	 * We need at least as many mbufs as we have clusters of
	 * the various types added together.
	 */
	TUNABLE_INT_FETCH("kern.ipc.nmbufs", &nmbufs);
	if (nmbufs < nmbclusters + nmbjumbop + nmbjumbo9 + nmbjumbo16)
		nmbufs = lmax(maxmbufmem / MSIZE / 5,
		    nmbclusters + nmbjumbop + nmbjumbo9 + nmbjumbo16);
}