#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ht_entry_struct {int dummy; } ;
typedef  TYPE_1__* ht_t ;
typedef  TYPE_2__* ht_entry_t ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
struct TYPE_6__ {size_t num_buckets; TYPE_2__** buckets; int /*<<< orphan*/  num_keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void ht_clear(ht_t self) {
  size_t i;
  for (i = 0; i < self->num_buckets; i++) {
    ht_entry_t curr = self->buckets[i];
    while (curr) {
      ht_entry_t next = curr->next;
      memset(curr, 0, sizeof(struct ht_entry_struct));
      free(curr);
      self->num_keys--;
      curr = next;
    }
    self->buckets[i] = NULL;
  }
}