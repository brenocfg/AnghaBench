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

/* Variables and functions */
 scalar_t__* __fpreg ; 

__attribute__((used)) static __inline u_int64_t
__fpu_getreg64(int r)
{

	return ((u_int64_t)__fpreg[r] << 32 | (u_int64_t)__fpreg[r + 1]);
}