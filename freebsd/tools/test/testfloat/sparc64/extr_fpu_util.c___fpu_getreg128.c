#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int64_t ;
struct TYPE_3__ {int high; int low; } ;
typedef  TYPE_1__ float128 ;

/* Variables and functions */
 scalar_t__* __fpreg ; 

__attribute__((used)) static __inline float128
__fpu_getreg128(int r)
{
	float128 v;

	v.high = ((u_int64_t)__fpreg[r] << 32 | (u_int64_t)__fpreg[r + 1]);
	v.low = ((u_int64_t)__fpreg[r + 2] << 32 | (u_int64_t)__fpreg[r + 3]);
	return (v);
}