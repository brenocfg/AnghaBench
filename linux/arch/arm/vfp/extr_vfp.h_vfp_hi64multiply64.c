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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int /*<<< orphan*/  mul64to128 (scalar_t__*,scalar_t__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline u64 vfp_hi64multiply64(u64 n, u64 m)
{
	u64 rh, rl;
	mul64to128(&rh, &rl, n, m);
	return rh | (rl != 0);
}