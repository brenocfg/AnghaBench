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
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  param_set; } ;
typedef  TYPE_1__ token ;

/* Variables and functions */
 int /*<<< orphan*/  dl_free (TYPE_1__*,int) ; 
 scalar_t__ end_token ; 
 scalar_t__ op_in ; 
 int /*<<< orphan*/  set_ll_free (int /*<<< orphan*/ *) ; 

void del_token_list (token *v) {
  if (v == NULL) {
    return;
  }

  token *t = v;
  while (t->type != end_token) {
    if (t->type == op_in) {
      set_ll_free (&t->param_set);
    }

    t++;
  }

  dl_free (v, (t - v + 1) * sizeof (token));
}