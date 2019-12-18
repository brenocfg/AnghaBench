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

/* Variables and functions */
 int /*<<< orphan*/  mirror_map_t ; 
 int /*<<< orphan*/ * mm_child ; 
 size_t offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline size_t
vdev_mirror_map_size(int children)
{
	return (offsetof(mirror_map_t, mm_child[children]) +
	    sizeof(int) * children);
}