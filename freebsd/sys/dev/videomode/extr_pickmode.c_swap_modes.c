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
struct videomode {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void
swap_modes(struct videomode *left, struct videomode *right)
{
	struct videomode temp;

	temp = *left;
	*left = *right;
	*right = temp;
}