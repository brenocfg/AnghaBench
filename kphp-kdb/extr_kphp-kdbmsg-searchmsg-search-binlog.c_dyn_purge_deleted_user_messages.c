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
struct TYPE_4__ {int* delmsg_list; int delmsg_cnt; int pos_to; int neg_to; TYPE_2__* msgs; } ;
typedef  TYPE_1__ user_mod_header_t ;
struct TYPE_5__ {int message_id; struct TYPE_5__* prev; } ;
typedef  TYPE_2__ message_t ;

/* Variables and functions */
 int /*<<< orphan*/  purged_msgs_cnt ; 

void dyn_purge_deleted_user_messages (user_mod_header_t *H) {
  int *A, *B;
  int pos_to, neg_to, msg_id;
  message_t *Msg, **ptr;

  if (!H || !H->delmsg_list || !H->delmsg_cnt || !H->msgs) {
    return;
  }

  A = H->delmsg_list;
  B = A + H->delmsg_cnt - 1;
  pos_to = H->pos_to;
  neg_to = H->neg_to;
  Msg = H->msgs;
  ptr = &H->msgs;

  while (Msg) {
    msg_id = Msg->message_id;
    if (msg_id > 0) {
      while (B >= A && *B > msg_id) { B--; }
      if ((B >= A && *B == msg_id) || msg_id <= pos_to) {
	*ptr = Msg = Msg->prev;
	purged_msgs_cnt++;
	continue;
      }
    } else {
      while (B >= A && *A < msg_id) { A++; }
      if ((B >= A && *A == msg_id) || msg_id >= neg_to) {
	*ptr = Msg = Msg->prev;
	purged_msgs_cnt++;
	continue;
      }
    }
    ptr = &Msg->prev;
    Msg = Msg->prev;
  }
}