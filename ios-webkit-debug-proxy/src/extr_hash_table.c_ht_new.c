#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ht_struct {int dummy; } ;
typedef  TYPE_1__* ht_t ;
typedef  int /*<<< orphan*/  ht_entry_t ;
typedef  enum ht_key_type { ____Placeholder_ht_key_type } ht_key_type ;
struct TYPE_4__ {int /*<<< orphan*/  on_cmp; int /*<<< orphan*/  on_hash; int /*<<< orphan*/  num_buckets; int /*<<< orphan*/ * buckets; } ;

/* Variables and functions */
 int HT_STRING_KEYS ; 
 int /*<<< orphan*/  NUM_BUCKETS ; 
 scalar_t__ calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  on_strcmp ; 
 int /*<<< orphan*/  on_strhash ; 

ht_t ht_new(enum ht_key_type type) {
  ht_t self = (ht_t)malloc(sizeof(struct ht_struct));
  if (self) {
    memset(self, 0, sizeof(struct ht_struct));
    self->num_buckets = NUM_BUCKETS;
    self->buckets = (ht_entry_t *)calloc(self->num_buckets,
        sizeof(ht_entry_t));
    if (type == HT_STRING_KEYS) {
      self->on_hash = on_strhash;
      self->on_cmp = on_strcmp;
    }
  }
  return self;
}