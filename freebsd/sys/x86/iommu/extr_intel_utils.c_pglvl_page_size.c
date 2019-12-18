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
typedef  int dmar_gaddr_t ;

/* Variables and functions */
#define  DMAR_NPTEPGSHIFT 129 
#define  DMAR_PAGE_SIZE 128 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int nitems (int const*) ; 

dmar_gaddr_t
pglvl_page_size(int total_pglvl, int lvl)
{
	int rlvl;
	static const dmar_gaddr_t pg_sz[] = {
		(dmar_gaddr_t)DMAR_PAGE_SIZE,
		(dmar_gaddr_t)DMAR_PAGE_SIZE << DMAR_NPTEPGSHIFT,
		(dmar_gaddr_t)DMAR_PAGE_SIZE << (2 * DMAR_NPTEPGSHIFT),
		(dmar_gaddr_t)DMAR_PAGE_SIZE << (3 * DMAR_NPTEPGSHIFT),
		(dmar_gaddr_t)DMAR_PAGE_SIZE << (4 * DMAR_NPTEPGSHIFT),
		(dmar_gaddr_t)DMAR_PAGE_SIZE << (5 * DMAR_NPTEPGSHIFT)
	};

	KASSERT(lvl >= 0 && lvl < total_pglvl,
	    ("total %d lvl %d", total_pglvl, lvl));
	rlvl = total_pglvl - lvl - 1;
	KASSERT(rlvl < nitems(pg_sz), ("sizeof pg_sz lvl %d", lvl));
	return (pg_sz[rlvl]);
}