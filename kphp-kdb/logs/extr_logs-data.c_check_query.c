#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* root; } ;
typedef  TYPE_2__ expression ;
typedef  int /*<<< orphan*/  event ;
struct TYPE_5__ {int v_int; } ;
struct TYPE_7__ {TYPE_1__ tok; } ;

/* Variables and functions */
 scalar_t__ recalc_tree (TYPE_3__*,int /*<<< orphan*/ *) ; 

inline int check_query (expression *expr, event *e) {
  if (recalc_tree (expr->root, e)) {
    return expr->root->tok.v_int;
  }
  return 0;
}