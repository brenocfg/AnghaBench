#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* r; struct TYPE_4__* l; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ wkey ;
struct TYPE_5__ {long long w_id; int /*<<< orphan*/  q_id; } ;

/* Variables and functions */
 size_t MAX_ANS ; 
 TYPE_3__* ans ; 
 size_t ans_n ; 

void dfs (wkey *v, long long id) {
  if (v == NULL || ans_n >= MAX_ANS) {
    return;
  }
  ans[ans_n].w_id = id;
  ans[ans_n].q_id = v->x;
  ans_n++;

  dfs (v->l, id);
  dfs (v->r, id);
}