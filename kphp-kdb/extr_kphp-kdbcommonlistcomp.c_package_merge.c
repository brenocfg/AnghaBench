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
struct ccp_list_entry {scalar_t__ freq; int leaf_value; struct ccp_list_entry* next; struct ccp_list_entry* right; struct ccp_list_entry* left; } ;

/* Variables and functions */
 struct ccp_list_entry* new_ccp_list_entry (scalar_t__) ; 

__attribute__((used)) static struct ccp_list_entry *package_merge (struct ccp_list_entry *x, struct ccp_list_entry *y) {
  struct ccp_list_entry *head = NULL, *tail = NULL;
  while (x != NULL) {
    if (x->next == NULL) {
      break;
    }
    struct ccp_list_entry *w = x->next, *p = new_ccp_list_entry (x->freq + w->freq);
    p->leaf_value = -1;
    p->left = x;
    p->right = w;
    x = w->next;

    if (head == NULL) {
      head = tail = p;
    } else {
      tail = tail->next = p;
    }
  }
  x = head;
  head = tail = NULL;
  while (x != NULL && y != NULL) {
    if (x->freq <= y->freq) {
      if (head == NULL) {
        head = tail = x;
      } else {
        tail = tail->next = x;
      }
      x = x->next;
    } else {
      if (head == NULL) {
        head = tail = y;
      } else {
        tail = tail->next = y;
      }
      y = y->next;
    }
  }
  if (y != NULL) {
    x = y;
  }
  if (head == NULL) {
    return x;
  }
  tail->next = x;
  return head;
}