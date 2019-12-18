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
typedef  int /*<<< orphan*/  user_t ;
struct lev_rate {scalar_t__ type; int /*<<< orphan*/  rate; int /*<<< orphan*/  user_id; } ;

/* Variables and functions */
 scalar_t__ LEV_TARG_RATE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * get_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rate_change (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void set_rate (struct lev_rate *E) {
  assert (E->type == LEV_TARG_RATE);
  user_t *U = get_user (E->user_id);
  if (U) {
    rate_change (U, E->rate);
  }
}