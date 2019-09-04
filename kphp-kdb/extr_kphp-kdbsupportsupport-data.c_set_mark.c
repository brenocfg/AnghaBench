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
struct lev_support_set_mark {int user_id; int mark; } ;

/* Variables and functions */
 int change_mark (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int set_mark (struct lev_support_set_mark *E) {
  if (verbosity > 1) {
    fprintf (stderr, "Setting mark for question %d to %d\n", E->user_id, E->mark);
  }

  return change_mark (E->user_id, E->mark);
}