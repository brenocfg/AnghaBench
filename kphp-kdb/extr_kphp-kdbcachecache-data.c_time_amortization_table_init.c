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
struct time_amortization_table {double c; double T; double* hi_exp; double* lo_exp; } ;

/* Variables and functions */
 int AMORTIZATION_TABLE_SQRT_SIZE ; 
 double M_LN2 ; 
 double exp (int) ; 

void time_amortization_table_init (struct time_amortization_table *self, double T) {
  int i;
  self->c = -(M_LN2 / T);
  self->T = T;
  const double hi_mult = exp (self->c * AMORTIZATION_TABLE_SQRT_SIZE), lo_mult = exp (self->c);
  self->hi_exp[0] = self->lo_exp[0] = 1.0;
  for (i = 1; i < AMORTIZATION_TABLE_SQRT_SIZE; i++) {
    self->hi_exp[i] = self->hi_exp[i-1] * hi_mult;
    self->lo_exp[i] = self->lo_exp[i-1] * lo_mult;
  }
}