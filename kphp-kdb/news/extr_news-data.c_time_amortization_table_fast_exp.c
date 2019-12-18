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
struct TYPE_2__ {double* hi_exp; double* lo_exp; int c; } ;

/* Variables and functions */
 int AMORTIZATION_TABLE_SQRT_SIZE ; 
 int AMORTIZATION_TABLE_SQRT_SIZE_BITS ; 
 int AMORTIZATION_TABLE_SQRT_SIZE_MASK ; 
 TYPE_1__ TAT ; 
 double exp (int) ; 

__attribute__((used)) static inline double time_amortization_table_fast_exp (int dt) {
  return (dt < AMORTIZATION_TABLE_SQRT_SIZE * AMORTIZATION_TABLE_SQRT_SIZE) ?
          TAT.hi_exp[dt >> AMORTIZATION_TABLE_SQRT_SIZE_BITS] * TAT.lo_exp[dt & AMORTIZATION_TABLE_SQRT_SIZE_MASK] :
          exp (TAT.c * dt);
}