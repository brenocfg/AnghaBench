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
struct mce {scalar_t__ bank; scalar_t__ status; scalar_t__ addr; scalar_t__ misc; } ;

/* Variables and functions */

__attribute__((used)) static inline bool mce_cmp(struct mce *m1, struct mce *m2)
{
	return m1->bank != m2->bank ||
		m1->status != m2->status ||
		m1->addr != m2->addr ||
		m1->misc != m2->misc;
}