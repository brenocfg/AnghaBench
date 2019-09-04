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
struct TYPE_6__ {int real_priority; long long task_id; int time_received; int /*<<< orphan*/  id; TYPE_1__* l; struct TYPE_6__* next; } ;
typedef  TYPE_2__ temp_letter ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int data_len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int DELAYED_TABLE_SIZE ; 
 int GET_DELAYED_ID (scalar_t__) ; 
 int MAX_DELAY ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* delayed_head_letter ; 
 int /*<<< orphan*/  delete_letter (int /*<<< orphan*/ ) ; 
 int get_fields (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_deleted_task (long long,int) ; 
 int last_process_delayed_time ; 
 int /*<<< orphan*/  letter_add (int,int /*<<< orphan*/ ) ; 
 TYPE_3__* letter_buf ; 
 int /*<<< orphan*/ * letter_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ now ; 
 int strlen (int /*<<< orphan*/ ) ; 

void process_delayed_letters (int all, int skip) {
  while (letter_get (0) != NULL) {
  }

  int en = GET_DELAYED_ID(now + 1 + all * MAX_DELAY);

  while (last_process_delayed_time != en) {
    temp_letter *cur_letter = &delayed_head_letter[last_process_delayed_time];
    if (cur_letter->next != cur_letter) {
      cur_letter = cur_letter->next;

      int len = strlen (cur_letter->l->data);
      assert (len < cur_letter->l->data_len);
      memcpy (letter_buf->data, cur_letter->l->data, len + 1);

      assert (get_fields (letter_buf->data) >= 4);

      int real_priority = skip ? 0 : cur_letter->real_priority;
      long long task_id = cur_letter->task_id;
      int time_received = cur_letter->time_received;

      delete_letter (cur_letter->id);
      //DO NOT USE LETTER AFTER DELETE

      if (!is_deleted_task (task_id, time_received)) {
        letter_add (real_priority, 0);
      }
    } else {
      if (++last_process_delayed_time == DELAYED_TABLE_SIZE) {
        last_process_delayed_time = 0;
      }
    }
  }
  if (--last_process_delayed_time == -1) {
    last_process_delayed_time = DELAYED_TABLE_SIZE - 1;
  }
}