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
typedef  int /*<<< orphan*/  tree_t ;
struct TYPE_4__ {scalar_t__ Sp; } ;
typedef  TYPE_1__ tree_iterator_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ti_dive_right (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree_t *ti_init_right (tree_iterator_t *I, tree_t *T) {
  I->Sp = 0;
  if (T) {
    return ti_dive_right (I, T);
  } else {
    return 0;
  }
}