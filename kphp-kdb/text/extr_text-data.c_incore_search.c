#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  msg_tree; struct msg_search_node* last; int /*<<< orphan*/  edit_text_tree; } ;
typedef  TYPE_3__ user_t ;
struct TYPE_12__ {int x; int y; TYPE_2__* msg; TYPE_1__* edit_text; } ;
typedef  TYPE_4__ tree_t ;
typedef  int /*<<< orphan*/  tree_iterator_t ;
struct msg_search_node {int local_id; int /*<<< orphan*/  words_num; int /*<<< orphan*/  words; struct msg_search_node* prev; } ;
struct TYPE_10__ {int flags; scalar_t__ peer_id; scalar_t__ date; int /*<<< orphan*/  len; scalar_t__ text; } ;
struct TYPE_9__ {struct msg_search_node* search_node; } ;

/* Variables and functions */
 int MAX_SEARCH_SCANNED_INCORE_MESSAGES ; 
 int /*<<< orphan*/  QWords ; 
 int /*<<< orphan*/  Qn ; 
 scalar_t__ Qq ; 
 int TF_PLUS ; 
 int /*<<< orphan*/  aho_check_message (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ list_contained (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int s_and_mask ; 
 scalar_t__ s_max_time ; 
 scalar_t__ s_min_time ; 
 scalar_t__ s_peer_id ; 
 int s_xor_mask ; 
 scalar_t__ text_shift ; 
 TYPE_4__* ti_init_right (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* ti_next_right (int /*<<< orphan*/ *) ; 
 TYPE_4__* tree_lookup (int /*<<< orphan*/ ,int) ; 

int incore_search (user_t *U, int max_res, int *Res) {
  struct msg_search_node *cur;
  int max_scanned_messages = MAX_SEARCH_SCANNED_INCORE_MESSAGES;
  int i = 0;
  static tree_iterator_t I;
  tree_t *Z = ti_init_right (&I, U->edit_text_tree);

  for (cur = U->last; cur; cur = cur->prev) {

    struct msg_search_node *cur2 = cur;

    while (Z && Z->x > cur->local_id) {
      Z = ti_next_right (&I);
    }

    if (Z && Z->x == cur->local_id) {
      cur2 = Z->edit_text->search_node;
      Z = ti_next_right (&I);
    }
    
    if (list_contained (QWords, Qn, cur2->words, cur2->words_num)) {
      tree_t *T = tree_lookup (U->msg_tree, cur->local_id);
      if (T) {
        assert ((T->y & 7) == TF_PLUS);
        int flags = T->msg->flags;
        if (!((flags ^ s_xor_mask) & s_and_mask) && (!s_peer_id || T->msg->peer_id == s_peer_id) && T->msg->date >= s_min_time && T->msg->date < s_max_time) {
          if (Qq) {
            if (!--max_scanned_messages) {
              break;
            }
            if (!aho_check_message (T->msg->text + text_shift, T->msg->len)) {
              continue;
            }
          }
          Res[i++] = cur->local_id;
          if (i >= max_res) {
            return i;
          }
        }
      }
    }
  }

  return i;
}