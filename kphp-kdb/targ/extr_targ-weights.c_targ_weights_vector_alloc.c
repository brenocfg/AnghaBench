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
typedef  int /*<<< orphan*/  targ_weights_vector_t ;

/* Variables and functions */
 int get_vector_size () ; 
 int tot_weights_vector_bytes ; 
 int /*<<< orphan*/  tot_weights_vectors ; 
 int /*<<< orphan*/ * zmalloc0 (int) ; 

targ_weights_vector_t *targ_weights_vector_alloc (void) {
  int sz = get_vector_size ();
  tot_weights_vectors++;
  tot_weights_vector_bytes += sz;
  return zmalloc0 (sz);
}