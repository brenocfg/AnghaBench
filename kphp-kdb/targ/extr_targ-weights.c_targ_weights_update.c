#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* weights; } ;
typedef  TYPE_1__ user_t ;
struct TYPE_5__ {int* values; } ;

/* Variables and functions */
 int /*<<< orphan*/ * TAT ; 
 TYPE_1__* get_user (int) ; 
 TYPE_2__* targ_weights_vector_alloc () ; 
 int weights_coords ; 
 int /*<<< orphan*/  weights_updates ; 

int targ_weights_update (int vector_id, int relaxation_time, int coords, int *values) {
  if (coords != weights_coords || TAT == NULL) {
    return -1;
  }
  user_t *U = get_user (vector_id);
  if (U == NULL) {
    return -1;
  }
  if (U->weights == NULL) {
    U->weights = targ_weights_vector_alloc ();
  }
  int i;
  for (i = 0; i < weights_coords; i++) {
    U->weights->values[i] = values[i] * (1.0 / 1073741824.0);
  }
  weights_updates++;
  return 0;
}