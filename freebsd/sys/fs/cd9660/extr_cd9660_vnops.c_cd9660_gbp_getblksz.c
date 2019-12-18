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
struct vnode {int dummy; } ;
struct iso_node {int /*<<< orphan*/  i_mnt; } ;
typedef  int /*<<< orphan*/  daddr_t ;

/* Variables and functions */
 struct iso_node* VTOI (struct vnode*) ; 
 int blksize (int /*<<< orphan*/ ,struct iso_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cd9660_gbp_getblksz(struct vnode *vp, daddr_t lbn)
{
	struct iso_node *ip;

	ip = VTOI(vp);
	return (blksize(ip->i_mnt, ip, lbn));
}