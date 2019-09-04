#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  keys_cnt; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ queue ;
struct TYPE_8__ {int timeout; int /*<<< orphan*/ * prev_time; int /*<<< orphan*/  next_time; int /*<<< orphan*/ * prev_st; int /*<<< orphan*/  st; TYPE_1__* q; scalar_t__ lock; } ;
typedef  TYPE_2__ qkey ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int engine_id ; 
 int /*<<< orphan*/  qkey_fix_timeout (TYPE_2__*) ; 
 TYPE_2__* qkey_get (int /*<<< orphan*/ ,int) ; 

void update_news (queue *q) {
  qkey *mk = qkey_get (q->name, 2);

  dbg ("update news [%s] mk = %p\n", q->name, mk);

  if (mk->q == NULL) {
    mk->q = q;
    mk->lock = 0;
    mk->q->keys_cnt++;
    mk->st = mk->prev_st = NULL;

#ifdef TEST_MODE
    mk->timeout = 200;
#else
    mk->timeout = 20 * (engine_id % 2 + 1);
#endif
    mk->next_time = mk->prev_time = NULL;
  }
  qkey_fix_timeout (mk);
}