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
struct oidmap_iter {int dummy; } ;
struct oidmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  oidmap_iter_init (struct oidmap*,struct oidmap_iter*) ; 
 scalar_t__ oidmap_iter_next (struct oidmap_iter*) ; 

__attribute__((used)) static inline void *oidmap_iter_first(struct oidmap *map,
				      struct oidmap_iter *iter)
{
	oidmap_iter_init(map, iter);
	/* TODO: this API could be reworked to do compile-time type checks */
	return (void *)oidmap_iter_next(iter);
}