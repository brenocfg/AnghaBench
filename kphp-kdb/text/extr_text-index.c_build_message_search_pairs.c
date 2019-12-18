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
struct search_index_pair {int /*<<< orphan*/  idx; int /*<<< orphan*/  crc; } ;
struct TYPE_3__ {int /*<<< orphan*/  local_id; int /*<<< orphan*/  len; scalar_t__ text; } ;
typedef  TYPE_1__ message_t ;

/* Variables and functions */
 int MAX_TEXT_LEN ; 
 int /*<<< orphan*/ * WordCRC ; 
 int /*<<< orphan*/  assert (int) ; 
 int compute_message_distinct_words (scalar_t__*,int) ; 
 scalar_t__* dyn_cur ; 
 scalar_t__* dyn_top ; 
 scalar_t__ text_shift ; 
 int unpack_message (scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void build_message_search_pairs (message_t *msg) {
  assert (dyn_top >= dyn_cur + MAX_TEXT_LEN);

  int msg_len = unpack_message (dyn_cur, msg->text + text_shift, msg->len);
  assert (msg_len >= 0 && msg_len < MAX_TEXT_LEN);
  dyn_cur[msg_len] = 0;

  //fprintf (stderr, "message, local_id=%d: len=%d '%s'\n", msg->local_id, msg_len, dyn_cur);

  int cnt = compute_message_distinct_words (dyn_cur, msg_len);

  dyn_top -= cnt * sizeof (struct search_index_pair);
  assert (dyn_cur <= dyn_top);

  struct search_index_pair *ptr = (struct search_index_pair *)dyn_top;

  int i;
  for (i = 0; i < cnt; i++, ptr++) {
    ptr->crc = WordCRC[i];
    ptr->idx = msg->local_id;
  }
}