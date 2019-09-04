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
struct list_itemid_entry {struct list_itemid_entry* next; int /*<<< orphan*/  item_id; } ;

/* Variables and functions */
 scalar_t__ do_delete_item (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flushing_binlog_check () ; 
 int /*<<< orphan*/  free_all_list_decoders () ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 
 int /*<<< orphan*/  zfree (struct list_itemid_entry*,int) ; 

int do_delete_items_list (struct list_itemid_entry *head) {
  struct list_itemid_entry *p;
  int tot_deleted = 0;
  for (p = head; p != NULL; p = head) {
    if (do_delete_item (p->item_id)) {
      tot_deleted++;
      flushing_binlog_check ();
    }
    head = p->next;
    zfree (p, sizeof (struct list_itemid_entry));
  }
  vkprintf (1, "%d items was deleted.\n", tot_deleted);
  free_all_list_decoders ();
  return tot_deleted;
}