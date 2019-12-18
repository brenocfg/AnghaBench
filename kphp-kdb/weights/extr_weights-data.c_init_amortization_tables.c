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
struct lev_weights_set_half_life {int type; int half_life; } ;

/* Variables and functions */
 int /*<<< orphan*/ ** TAT ; 
 int WEIGHTS_MAX_COORDS ; 
 int /*<<< orphan*/  weights_set_half_life (struct lev_weights_set_half_life*) ; 

__attribute__((used)) static void init_amortization_tables (void) {
  int i;
  for (i = 0; i < WEIGHTS_MAX_COORDS; i++) {
    if (TAT[i] == NULL) {
      struct lev_weights_set_half_life E;
      E.type = i;
      E.half_life = 86400 * 30;
      weights_set_half_life (&E);
    }
  }
}