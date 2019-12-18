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
struct xbb_xen_reqlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * xbb_reqlist_bounce_addr (struct xbb_xen_reqlist*,int,int) ; 
 int /*<<< orphan*/ * xbb_reqlist_vaddr (struct xbb_xen_reqlist*,int,int) ; 

__attribute__((used)) static inline uint8_t *
xbb_reqlist_ioaddr(struct xbb_xen_reqlist *reqlist, int pagenr, int sector)
{
#ifdef XBB_USE_BOUNCE_BUFFERS
	return (xbb_reqlist_bounce_addr(reqlist, pagenr, sector));
#else
	return (xbb_reqlist_vaddr(reqlist, pagenr, sector));
#endif
}