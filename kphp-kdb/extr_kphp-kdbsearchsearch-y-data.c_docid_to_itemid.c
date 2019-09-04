#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {long long item_id; } ;

/* Variables and functions */
 TYPE_1__* IndexItems ; 
 long long MAX_ITEM_ID ; 
 int idx_items ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline long long docid_to_itemid (int doc_id) {
  if (unlikely(doc_id < 0)) {
    return -1LL;
  }
  if (unlikely(doc_id >= idx_items)) {
    return MAX_ITEM_ID;
  }
  return IndexItems[doc_id].item_id;
}