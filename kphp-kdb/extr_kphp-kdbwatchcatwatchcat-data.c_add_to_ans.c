#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  root; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; TYPE_1__ keys; } ;
typedef  TYPE_2__ watchcat ;

/* Variables and functions */
 int /*<<< orphan*/  dfs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 int my_verbosity ; 
 int /*<<< orphan*/  stderr ; 

void add_to_ans (watchcat *w) {
  if (my_verbosity > 2) {
    fprintf (stderr, "add to ans %p\n", w);
  }
  dfs (w->keys.root, w->id);
}