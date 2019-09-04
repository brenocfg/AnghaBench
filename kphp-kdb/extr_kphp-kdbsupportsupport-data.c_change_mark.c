#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* answers_list_ptr ;
struct TYPE_5__ {TYPE_1__* E; } ;
struct TYPE_4__ {int mark; } ;

/* Variables and functions */
 void** map_int_vptr_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  process_answer (TYPE_2__*,int) ; 
 int /*<<< orphan*/  user_id_to_answer ; 

int change_mark (int user_id, int mark) {
  void **cur_ = map_int_vptr_get (&user_id_to_answer, user_id);
  if (cur_ != NULL) {
    answers_list_ptr cur = *cur_;
    if (cur->E->mark != mark) {
      process_answer (cur, -1);
      cur->E->mark = mark;
      process_answer (cur, 1);
    }
  }

  return 1;
}