#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct list_itemid_entry {struct list_itemid_entry* next; int /*<<< orphan*/  item_id; } ;
struct TYPE_6__ {TYPE_4__* cur; } ;
typedef  TYPE_1__ iheap_en_t ;
struct TYPE_7__ {int /*<<< orphan*/  item_id; } ;

/* Variables and functions */
 TYPE_1__* IHE ; 
 scalar_t__ Q_order ; 
 int /*<<< orphan*/  clear_res () ; 
 int do_delete_items_list (struct list_itemid_entry*) ; 
 long long get_hash_item (TYPE_4__*) ; 
 int /*<<< orphan*/  ihe_advance (TYPE_1__*) ; 
 int /*<<< orphan*/  ihe_init (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  universal_tag_hash ; 
 struct list_itemid_entry* zmalloc (int) ; 

int do_delete_items_with_hash (long long hash) {
  struct list_itemid_entry *head = NULL, *tail = NULL, *p;
  if (hash == 0) {
    return 0;
  }
  Q_order = 0;
  clear_res ();

  if (!ihe_init (IHE, universal_tag_hash, 1, 0)) {
    return 0;
  }

  iheap_en_t *H = IHE;
  while (H->cur) {
    if (get_hash_item (H->cur) == hash) {
      p = zmalloc (sizeof (struct list_itemid_entry));
      p->item_id = H->cur->item_id;
      p->next = NULL;
      if (head) {
        tail->next = p;
        tail = p;
      } else {
        head = tail = p;
      }
    }
    ihe_advance (H);
  }
  return do_delete_items_list (head);
}