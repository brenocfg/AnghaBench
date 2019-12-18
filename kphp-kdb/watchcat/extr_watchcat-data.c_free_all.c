#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* l; } ;
typedef  TYPE_1__ wkey ;
struct TYPE_8__ {struct TYPE_8__* next_time; } ;

/* Variables and functions */
 int TIME_TABLE_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  del_wkey (TYPE_3__*) ; 
 int /*<<< orphan*/  dl_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  free_wkey (TYPE_3__*) ; 
 int /*<<< orphan*/  h_watchcat ; 
 int /*<<< orphan*/  h_watchcat_q ; 
 int /*<<< orphan*/  hset_llp_free (int /*<<< orphan*/ *) ; 
 scalar_t__ keys_cnt ; 
 TYPE_3__** time_st ; 
 scalar_t__ verbosity ; 
 TYPE_1__* wkey_mem ; 

void free_all (void) {
  if (verbosity) {
    keys_cnt += TIME_TABLE_SIZE;
    int i;
    for (i = 0; i < TIME_TABLE_SIZE; i++) {
      while (time_st[i]->next_time != time_st[i]) {
        del_wkey (time_st[i]->next_time);
      }
      free_wkey (time_st[i]);
    }
    assert (keys_cnt == 0);

    while (wkey_mem != NULL) {
      wkey *k = wkey_mem;
      wkey_mem = wkey_mem->l;
      dl_free (k, sizeof (wkey));
    }

    hset_llp_free (&h_watchcat);
    hset_llp_free (&h_watchcat_q);
  }
}