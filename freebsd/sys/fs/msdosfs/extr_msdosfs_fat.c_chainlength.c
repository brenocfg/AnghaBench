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
typedef  size_t u_long ;
typedef  unsigned int u_int ;
struct msdosfsmount {size_t pm_maxcluster; unsigned int* pm_inusemap; } ;

/* Variables and functions */
 size_t MIN (size_t,size_t) ; 
 int /*<<< orphan*/  MSDOSFS_ASSERT_MP_LOCKED (struct msdosfsmount*) ; 
 size_t N_INUSEBITS ; 
 int ffs (unsigned int) ; 

__attribute__((used)) static int
chainlength(struct msdosfsmount *pmp, u_long start, u_long count)
{
	u_long idx, max_idx;
	u_int map;
	u_long len;

	MSDOSFS_ASSERT_MP_LOCKED(pmp);

	if (start > pmp->pm_maxcluster)
		return (0);
	max_idx = pmp->pm_maxcluster / N_INUSEBITS;
	idx = start / N_INUSEBITS;
	start %= N_INUSEBITS;
	map = pmp->pm_inusemap[idx];
	map &= ~((1U << start) - 1);
	if (map) {
		len = ffs(map) - 1 - start;
		len = MIN(len, count);
		if (start + len > pmp->pm_maxcluster)
			len = pmp->pm_maxcluster - start + 1;
		return (len);
	}
	len = N_INUSEBITS - start;
	if (len >= count) {
		len = count;
		if (start + len > pmp->pm_maxcluster)
			len = pmp->pm_maxcluster - start + 1;
		return (len);
	}
	while (++idx <= max_idx) {
		if (len >= count)
			break;
		map = pmp->pm_inusemap[idx];
		if (map) {
			len += ffs(map) - 1;
			break;
		}
		len += N_INUSEBITS;
	}
	len = MIN(len, count);
	if (start + len > pmp->pm_maxcluster)
		len = pmp->pm_maxcluster - start + 1;
	return (len);
}