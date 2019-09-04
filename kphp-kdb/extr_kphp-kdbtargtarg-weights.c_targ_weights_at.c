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
struct TYPE_3__ {int relaxation_time; double* values; } ;
typedef  TYPE_1__ targ_weights_vector_t ;

/* Variables and functions */
 int /*<<< orphan*/ * TAT ; 
 int log_last_ts ; 
 double time_amortization_table_fast_exp (int /*<<< orphan*/ ,int const) ; 
 int weights_coords ; 

double targ_weights_at (targ_weights_vector_t *weights, int coord_id) {
  if (weights == NULL || coord_id < 0 || coord_id >= weights_coords || TAT == NULL) {
    return 0.0;
  }
  const int dt = log_last_ts - weights->relaxation_time;
  double r = weights->values[coord_id];
  if (dt > 0) {
    r *= time_amortization_table_fast_exp (TAT[coord_id], dt);
  }
  return r;
}