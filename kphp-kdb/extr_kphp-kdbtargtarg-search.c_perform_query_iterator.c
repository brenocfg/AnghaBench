#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* iterator_t ;
struct TYPE_4__ {int pos; int (* jump_to ) (TYPE_1__*,int) ;} ;

/* Variables and functions */
 int INFTY ; 
 int /*<<< orphan*/  PROFILER (int) ; 
 int /*<<< orphan*/  Qq ; 
 int R_tot ; 
 TYPE_1__* build_iterator_from_query (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  postprocess_res () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  store_res (int) ; 
 int stub1 (TYPE_1__*,int) ; 
 int verbosity ; 

int perform_query_iterator (void) {
  if (verbosity > 1) {
    fprintf (stderr, "performing query via iterators\n");
  }

  PROFILER (6);

  iterator_t I = build_iterator_from_query (Qq, 1);

  PROFILER (7);

  int x = I->pos;
  while (x < INFTY) {
    store_res (x);
    x = I->jump_to (I, x + 1);
  }

  PROFILER (8);

  postprocess_res ();

  PROFILER (9);

  return R_tot;
}