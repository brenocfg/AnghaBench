#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ht_t ;
typedef  TYPE_2__* ht_entry_t ;
struct TYPE_5__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; struct TYPE_5__* next; } ;
struct TYPE_4__ {size_t num_buckets; TYPE_2__** buckets; scalar_t__ num_keys; } ;

/* Variables and functions */
 scalar_t__ calloc (scalar_t__,int) ; 

void **ht_get_all(ht_t self, int want_key) {
  void **ret = (void **)calloc(self->num_keys+1, sizeof(void *));
  if (ret) {
    void **tail = ret;
    size_t i;
    for (i = 0; i < self->num_buckets; i++) {
      ht_entry_t curr;
      for (curr = self->buckets[i]; curr; curr = curr->next) {
        *tail++ = (want_key ? curr->key : curr->value);
      }
    }
  }
  return ret;
}