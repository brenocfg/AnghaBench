#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct hashset_ll {int dummy; } ;
struct TYPE_7__ {TYPE_4__* cur; } ;
typedef  TYPE_1__ iheap_en_t ;
struct TYPE_8__ {int /*<<< orphan*/  item_id; } ;

/* Variables and functions */
 TYPE_1__* IHE ; 
 scalar_t__ Q_order ; 
 int /*<<< orphan*/  assign_max_set_rate_calls ; 
 int /*<<< orphan*/  clear_res () ; 
 int /*<<< orphan*/  do_set_rate_new (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  flushing_binlog_check () ; 
 int /*<<< orphan*/  free_all_list_decoders () ; 
 long long get_hash_item (TYPE_4__*) ; 
 int get_rate_item (TYPE_4__*,int) ; 
 scalar_t__ hashset_ll_get (struct hashset_ll*,long long const) ; 
 int /*<<< orphan*/  ihe_advance (TYPE_1__*) ; 
 int /*<<< orphan*/  ihe_init (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  universal_tag_hash ; 

int do_assign_max_rate_using_hashset (struct hashset_ll *HS, int rate_id, int value) {
  Q_order = 0;
  clear_res ();

  if (!ihe_init (IHE, universal_tag_hash, 1, 0)) {
    return 0;
  }

  iheap_en_t *H = IHE;
  while (H->cur) {
    const long long item_hash = get_hash_item (H->cur);
    if (item_hash && hashset_ll_get (HS, item_hash)) {
      int old_rate = get_rate_item (H->cur, rate_id);
      if (old_rate < value) {
        assign_max_set_rate_calls++;
        do_set_rate_new (H->cur->item_id, rate_id, value);
        flushing_binlog_check ();
      }
    }
    ihe_advance (H);
  }
  free_all_list_decoders ();
  return 1;
}