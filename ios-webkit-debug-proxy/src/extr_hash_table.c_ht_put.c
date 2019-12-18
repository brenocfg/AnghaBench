#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct ht_entry_struct {int dummy; } ;
typedef  TYPE_1__* ht_t ;
typedef  TYPE_2__* ht_entry_t ;
struct TYPE_11__ {intptr_t hc; struct TYPE_11__* next; int /*<<< orphan*/ * value; void* key; } ;
struct TYPE_10__ {int /*<<< orphan*/  num_keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  ht_find (TYPE_1__*,void*,intptr_t*,TYPE_2__***,TYPE_2__**,TYPE_2__**) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void *ht_put(ht_t self, void *key, void *value) {
  ht_entry_t *head;
  ht_entry_t prev;
  ht_entry_t curr;
  intptr_t hc;
  ht_find(self, key, &hc, &head, &prev, &curr);
  void *ret = (curr ? curr->value : NULL);
  if (curr) {
    if (value) {
      curr->value = value;
    } else {
      if (prev) {
        prev->next = curr->next;
      } else {
        *head = curr->next;
      }
      free(curr);
      self->num_keys--;
    }
  } else if (value) {
    curr = (ht_entry_t)malloc(sizeof(struct ht_entry_struct));
    // if (!curr) ?
    memset(curr, 0, sizeof(struct ht_entry_struct));
    curr->hc = hc;
    curr->key = key;
    curr->value = value;
    curr->next = *head;
    *head = curr;
    self->num_keys++;
  }
  return ret;
}