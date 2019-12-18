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
typedef  int /*<<< orphan*/  uint8_t ;
struct xbb_xen_reqlist {int /*<<< orphan*/ * kva; } ;

/* Variables and functions */
 int PAGE_SIZE ; 

__attribute__((used)) static inline uint8_t *
xbb_reqlist_vaddr(struct xbb_xen_reqlist *reqlist, int pagenr, int sector)
{
	return (reqlist->kva + (PAGE_SIZE * pagenr) + (sector << 9));
}