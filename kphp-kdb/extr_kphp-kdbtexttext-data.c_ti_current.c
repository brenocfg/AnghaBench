#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree_t ;
struct TYPE_3__ {int Sp; int /*<<< orphan*/ ** St; } ;
typedef  TYPE_1__ tree_iterator_t ;

/* Variables and functions */

__attribute__((used)) static inline tree_t *ti_current (tree_iterator_t *I) {
  return I->Sp ? I->St[I->Sp - 1] : 0;
}