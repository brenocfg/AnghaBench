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
struct tl_type {int flags; int params_num; long long params_types; char* id; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

int tl_type_set_params (struct tl_type *t, int x, long long y) {
  if (t->flags & 4) {
    t->params_num = x;
    t->params_types = y;
    t->flags &= ~4;
  } else {
    if (t->params_num != x || t->params_types != y) {
      fprintf (stderr, "Wrong num of params (type %s)\n", t->id);
      return 0;
    }
  }
  return 1;
}