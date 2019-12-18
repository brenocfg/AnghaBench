#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vnode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  attr_cache_timeout; } ;

/* Variables and functions */
 TYPE_1__* VTOFUD (struct vnode*) ; 
 int /*<<< orphan*/  bintime_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
fuse_vnode_clear_attr_cache(struct vnode *vp)
{
	bintime_clear(&VTOFUD(vp)->attr_cache_timeout);
}