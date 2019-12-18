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
typedef  int /*<<< orphan*/  user_t ;
struct lev_add_message {int text_len; long long legacy_id; int type; int ua_hash; int /*<<< orphan*/  user_id; scalar_t__ text; } ;
struct TYPE_3__ {int /*<<< orphan*/  user_id; } ;

/* Variables and functions */
 int LEV_TX_ADD_MESSAGE_EXT ; 
 int LEV_TX_ADD_MESSAGE_EXT_LL ; 
 int LEV_TX_ADD_MESSAGE_EXT_ZF ; 
 int MAX_EXTRA_MASK ; 
 TYPE_1__** User ; 
 int* UserMsgBytes ; 
 int /*<<< orphan*/ * UserMsgCnt ; 
 scalar_t__* UserSearchWords ; 
 int /*<<< orphan*/  assert (int) ; 
 int compute_message_distinct_words (scalar_t__,int) ; 
 int conv_uid (int /*<<< orphan*/ ) ; 
 int current_extra_mask ; 
 int /*<<< orphan*/  discarded_rec ; 
 int /*<<< orphan*/  last_global_id ; 
 long long max_legacy_id ; 
 int max_uid ; 
 int /*<<< orphan*/  max_user_search_id ; 
 scalar_t__ max_user_search_words ; 
 long long min_legacy_id ; 
 int msgs_bytes ; 
 int /*<<< orphan*/  msgs_read ; 
 int /*<<< orphan*/  preprocess_text (scalar_t__,int) ; 
 scalar_t__ search_enabled ; 
 int tot_search_words ; 
 int /*<<< orphan*/  tot_users ; 
 TYPE_1__* zmalloc0 (int) ; 

void process_message0 (struct lev_add_message *E, int extra_bytes) {
  int uid = conv_uid (E->user_id);
  int bytes = E->text_len;
  if (uid < 0) {
    discarded_rec++;
    return;
  }
  last_global_id++;
  if (!User[uid]) {
    User[uid] = zmalloc0 (sizeof (user_t));
    User[uid]->user_id = E->user_id;
    tot_users++;
  }
  long long legacy_id = E->legacy_id;
  if ((E->type & ~MAX_EXTRA_MASK) == LEV_TX_ADD_MESSAGE_EXT_LL) {
    legacy_id = (legacy_id & 0xffffffffLL) | (E->ua_hash & 0xffffffff00000000LL);
  }
  if (legacy_id < min_legacy_id) {
    min_legacy_id = legacy_id;
  }
  if (legacy_id > max_legacy_id) {
    max_legacy_id = legacy_id;
  }
  if (extra_bytes) {
    assert (!(E->type & MAX_EXTRA_MASK & ~current_extra_mask));
  } else {
    assert ((E->type & ~MAX_EXTRA_MASK) != LEV_TX_ADD_MESSAGE_EXT && (E->type & ~MAX_EXTRA_MASK) != LEV_TX_ADD_MESSAGE_EXT_ZF); // LL is allowed
  }
  preprocess_text (E->text + extra_bytes, bytes);

  if (search_enabled) {
    int d_words = compute_message_distinct_words (E->text + extra_bytes, bytes);
    tot_search_words += d_words;
    UserSearchWords[uid] += d_words;
    if (UserSearchWords[uid] > max_user_search_words) {
      max_user_search_words = UserSearchWords[uid];
      max_user_search_id = E->user_id;
    }
  }

  msgs_read++;
  msgs_bytes += bytes;

  if (uid > max_uid) {
    max_uid = uid;
  }
  UserMsgCnt[uid]++;
  UserMsgBytes[uid] += bytes;
}