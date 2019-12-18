#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lev_generic {int dummy; } ;
struct TYPE_2__ {int tot_lists; } ;

/* Variables and functions */
 TYPE_1__ Header ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  insert_postponed (int,struct lev_generic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_event_size (struct lev_generic*) ; 

void postpone (int x, struct lev_generic *E) {
  assert (0 <= x && x < Header.tot_lists);
  insert_postponed (x, E, log_event_size (E));
}