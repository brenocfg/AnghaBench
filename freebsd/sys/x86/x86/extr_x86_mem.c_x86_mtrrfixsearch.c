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
typedef  scalar_t__ u_int64_t ;
struct mem_range_softc {struct mem_range_desc* mr_desc; } ;
struct mem_range_desc {scalar_t__ mr_base; scalar_t__ mr_len; } ;

/* Variables and functions */
 int MTRR_N16K ; 
 int MTRR_N4K ; 
 int MTRR_N64K ; 

__attribute__((used)) static struct mem_range_desc *
x86_mtrrfixsearch(struct mem_range_softc *sc, u_int64_t addr)
{
	struct mem_range_desc *mrd;
	int i;

	for (i = 0, mrd = sc->mr_desc; i < MTRR_N64K + MTRR_N16K + MTRR_N4K;
	     i++, mrd++)
		if (addr >= mrd->mr_base &&
		    addr < mrd->mr_base + mrd->mr_len)
			return (mrd);
	return (NULL);
}