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
struct ccp_list_entry {struct ccp_list_entry* next; int /*<<< orphan*/  leaf_value; int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 struct ccp_list_entry* new_ccp_list_entry (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ccp_list_entry *zmalloc_ccp_list (struct ccp_list_entry *a, int M) {
  int i;
  struct ccp_list_entry *head = NULL, *tail = NULL;
  for (i = 0; i < M; i++) {
    struct ccp_list_entry *p = new_ccp_list_entry (a[i].freq);
    p->leaf_value = a[i].leaf_value;
    if (head == NULL) {
      head = tail = p;
    } else {
      tail = tail->next = p;
    }
  }
  return head;
}