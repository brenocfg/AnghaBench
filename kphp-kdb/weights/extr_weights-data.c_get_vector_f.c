#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int vector_id; int counters_mask; struct TYPE_7__* hnext; } ;
typedef  TYPE_1__ weights_vector_t ;

/* Variables and functions */
 TYPE_1__** H ; 
 int /*<<< orphan*/  add_use_front (TYPE_1__*) ; 
 int /*<<< orphan*/  del_use (TYPE_1__*) ; 
 int /*<<< orphan*/  tot_counters_arrays ; 
 int /*<<< orphan*/  tot_vectors ; 
 int vector_hash_prime ; 
 TYPE_1__* zmalloc0 (int) ; 

weights_vector_t *get_vector_f (int vector_id, int force) {
  const int h = vector_id % vector_hash_prime;
  weights_vector_t **p = &H[h], *V;
  while (*p) {
    V = *p;
    if (V->vector_id == vector_id) {
      *p = V->hnext;
      if (force >= 0) {
        V->hnext = H[h];
        H[h] = V;
      } else {
        del_use (V);
      }
      return V;
    }
    p = &V->hnext;
  }
  if (force > 0) {
    tot_vectors++;
    tot_counters_arrays++;
    V = zmalloc0 (sizeof (weights_vector_t));
    V->counters_mask = 1;
    V->vector_id = vector_id;
    V->hnext = H[h];
    add_use_front (V);
    return H[h] = V;
  }
  return NULL;
}