#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct index_item {int extra; } ;
struct TYPE_10__ {int extra; int mask; int /*<<< orphan*/  words; } ;
typedef  TYPE_1__ item_t ;
struct TYPE_11__ {int /*<<< orphan*/  freqs; int /*<<< orphan*/  word; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_NOT_FOUND_ITEM ; 
 int FLAG_DELETED ; 
 int /*<<< orphan*/  ONLY_FIND ; 
 TYPE_7__* Q ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clear_cur_wordlist () ; 
 int /*<<< orphan*/  creation_date ; 
 int /*<<< orphan*/  cur_wordlist_head ; 
 int /*<<< orphan*/  del_items ; 
 int evaluate_uniq_words_count (TYPE_7__*,int) ; 
 int extract_words (char const*,int,int /*<<< orphan*/ ,TYPE_7__*,int,int /*<<< orphan*/ ,long long) ; 
 int /*<<< orphan*/  fits (long long) ; 
 struct index_item* get_idx_item (long long) ; 
 int /*<<< orphan*/ * get_index_item_words_ptr (struct index_item*,int /*<<< orphan*/ ) ; 
 TYPE_1__* get_item_f (long long,int /*<<< orphan*/ ) ; 
 scalar_t__ import_only_mode ; 
 int /*<<< orphan*/  item_add_word (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_clear_wordlist (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_items ; 
 int /*<<< orphan*/  move_item_rates (TYPE_1__*,struct index_item*) ; 
 int now ; 
 int /*<<< orphan*/  set_multiple_rates_item (TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  tag_owner ; 
 int /*<<< orphan*/  universal ; 
 int /*<<< orphan*/  vkprintf (int,char*,char const*,int,long long,int,int) ; 
 scalar_t__ wordfreqs_enabled ; 

__attribute__((used)) static int change_item (const char *text, int len, long long item_id, int rate, int rate2) {
  item_t *I;
  struct index_item *II;

  assert (text && len >= 0 && len < 65536 && !text[len]);
  assert (item_id > 0);

  if (!fits (item_id)) {
    return 0;
  }

  if (import_only_mode) {
    return 1;
  }

  vkprintf (4, "change_item: text=%s, len = %d, item_id = %016llx, rate = %d, rate2 = %d\n",
    text, len, item_id, rate, rate2);

  II = get_idx_item (item_id);
  if (II) {
    mod_items++;
    II->extra |= FLAG_DELETED;
    item_clear_wordlist ((item_t *) II, get_index_item_words_ptr (II, 0));
  }

  I = get_item_f (item_id, ONLY_FIND);
  if (I) {
    if (I->extra & FLAG_DELETED) {
      del_items--;
      I->extra ^= FLAG_DELETED;
    }
    item_clear_wordlist (I, &I->words);
  } else {
    I = get_item_f (item_id, ADD_NOT_FOUND_ITEM);
    if (!I) {
      return 0;
    }
  }

  if (II) {
    move_item_rates (I, II);
  }

  int rates[4], mask = 1 + 2, l = 2;
  rates[0] = rate;
  rates[1] = rate2;
  if (!creation_date || !(I->mask & 4)) {
    rates[l++] = now;
    mask += 4;
  }

  clear_cur_wordlist ();
  int i, Wc = extract_words (text, len, universal, Q, 65536, tag_owner, item_id);
  for (i = 0; i < Wc; i++) {
    item_add_word (I, Q[i].word, Q[i].freqs);
  }
  I->words = cur_wordlist_head;
  if (wordfreqs_enabled) {
    rates[l++] = evaluate_uniq_words_count (Q, Wc);
    mask |= 1 << 13;
  }
  set_multiple_rates_item (I, mask, rates);
  return 1;
}