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
struct lev_weights_incr {int value; } ;

/* Variables and functions */
 scalar_t__ LEV_WEIGHTS_INCR ; 
 int WEIGHTS_MAX_COORDS ; 
 struct lev_weights_incr* alloc_log_event (scalar_t__,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int weights_incr (struct lev_weights_incr*) ; 

int do_weights_incr (int vector_id, int coord_id, int value) {
  //vkprintf (3, "%s: vector_id = %d, coord_id = %d, value = %d\n", __func__, vector_id, coord_id, value);
  assert (coord_id >= 0 && coord_id < WEIGHTS_MAX_COORDS);
  struct lev_weights_incr *E = alloc_log_event (LEV_WEIGHTS_INCR + coord_id, sizeof (*E), vector_id);
  E->value = value;
  return weights_incr (E);
}