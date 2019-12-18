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
struct mtx {int dummy; } ;

/* Variables and functions */
 uintptr_t ncvnodehash ; 
 struct mtx* vnodelocks ; 

__attribute__((used)) static inline struct mtx *
VP2VNODELOCK(struct vnode *vp)
{

	return (&vnodelocks[(((uintptr_t)(vp) >> 8) & ncvnodehash)]);
}