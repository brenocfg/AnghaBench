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
typedef  int u_int64_t ;
typedef  scalar_t__ u_int32_t ;

/* Variables and functions */
 scalar_t__* __fpreg ; 

__attribute__((used)) static __inline void
__fpu_setreg64(int r, u_int64_t v)
{

	__fpreg[r] = (u_int32_t)(v >> 32);
	__fpreg[r + 1] = (u_int32_t)v;
}