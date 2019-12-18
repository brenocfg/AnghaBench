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
struct oidmap_iter {int /*<<< orphan*/  h_iter; } ;

/* Variables and functions */
 scalar_t__ hashmap_iter_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void *oidmap_iter_next(struct oidmap_iter *iter)
{
	/* TODO: this API could be reworked to do compile-time type checks */
	return (void *)hashmap_iter_next(&iter->h_iter);
}