#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct item {int extra; } ;
struct index_item {int extra; } ;

/* Variables and functions */
 int FLAG_DELETED ; 
 int /*<<< orphan*/  ONLY_FIND ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  del_item_instances ; 
 int /*<<< orphan*/  del_items ; 
 int /*<<< orphan*/  delete_item_rates (struct item*) ; 
 struct index_item* get_idx_item (long long) ; 
 struct item* get_item_f (long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_clear_wordlist (struct item*) ; 
 int /*<<< orphan*/  mod_items ; 

__attribute__((used)) static int delete_item (long long item_id) {
  struct item *I = get_item_f (item_id, ONLY_FIND);
  struct index_item *II = get_idx_item (item_id);
  if (II) {
    II->extra |= FLAG_DELETED;
    mod_items++;
    assert (!I);
    return 1;
  }
  if (!I || (I->extra & FLAG_DELETED)) { return 0; }
  delete_item_rates (I);
  item_clear_wordlist (I);
  del_items++;
  del_item_instances++;
  return 1;
}