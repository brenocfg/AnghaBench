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
struct lev_weights_set_half_life {int dummy; } ;

/* Variables and functions */
 scalar_t__ LEV_WEIGHTS_SET_HALF_LIFE ; 
 int WEIGHTS_MAX_COORDS ; 
 struct lev_weights_set_half_life* alloc_log_event (scalar_t__,int,int) ; 
 int /*<<< orphan*/  unalloc_log_event (int) ; 
 int weights_set_half_life (struct lev_weights_set_half_life*) ; 

int do_weights_set_half_life (int coord_id, int half_life) {
  if (coord_id < 0 || coord_id >= WEIGHTS_MAX_COORDS || half_life <= 0) {
    return -1;
  }
  struct lev_weights_set_half_life *E = alloc_log_event (LEV_WEIGHTS_SET_HALF_LIFE + coord_id, sizeof (*E), half_life);
  int r = weights_set_half_life (E);
  if (r <= 0) {
    unalloc_log_event (sizeof (*E));
  }
  return r;
}