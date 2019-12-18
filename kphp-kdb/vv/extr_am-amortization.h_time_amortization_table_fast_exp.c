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
struct TYPE_3__ {double* hi_exp; double* lo_exp; int c; } ;
typedef  TYPE_1__ time_amortization_table_t ;

/* Variables and functions */
 int AMORTIZATION_TABLE_SQRT_SIZE ; 
 int AMORTIZATION_TABLE_SQRT_SIZE_BITS ; 
 int AMORTIZATION_TABLE_SQRT_SIZE_MASK ; 
 double exp (int) ; 

extern inline double time_amortization_table_fast_exp (time_amortization_table_t *self, int dt) {
  return (dt < AMORTIZATION_TABLE_SQRT_SIZE * AMORTIZATION_TABLE_SQRT_SIZE) ?
          self->hi_exp[dt >> AMORTIZATION_TABLE_SQRT_SIZE_BITS] * self->lo_exp[dt & AMORTIZATION_TABLE_SQRT_SIZE_MASK] :
          exp (self->c * dt);
}