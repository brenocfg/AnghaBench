#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ ev_first; } ;
typedef  TYPE_1__ queue ;
struct TYPE_8__ {struct TYPE_8__* next_time; scalar_t__ lock; int /*<<< orphan*/  timeout; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int TIME_TABLE_SIZE ; 
 int /*<<< orphan*/  alias ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  cr ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_qkey (TYPE_2__*) ; 
 int /*<<< orphan*/  dl_crypto_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_free (TYPE_1__*,int) ; 
 long long dl_get_memory_used () ; 
 int /*<<< orphan*/  epoll_close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long long) ; 
 int /*<<< orphan*/  h_qkey ; 
 int /*<<< orphan*/  h_queue ; 
 int /*<<< orphan*/  h_subscribers ; 
 int /*<<< orphan*/  hset_llp_free (int /*<<< orphan*/ *) ; 
 int http_sfd ; 
 scalar_t__ keys_cnt ; 
 int /*<<< orphan*/  map_int_int_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_ll_vptr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qkey_free (TYPE_2__*) ; 
 TYPE_1__* qs ; 
 int /*<<< orphan*/  secrets ; 
 int /*<<< orphan*/  shmap_string_vptr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_2__** time_st ; 
 long long treap_get_memory () ; 
 scalar_t__ verbosity ; 

void free_all (void) {
  if (verbosity) {
    //TODO close all connections
    if (http_sfd != -1) {
      epoll_close (http_sfd);
      assert (close (http_sfd) >= 0);
    }

    keys_cnt += TIME_TABLE_SIZE;
    int i;
    for (i = 0; i < TIME_TABLE_SIZE; i++) {
      while (time_st[i]->next_time != time_st[i]) {
        if (time_st[i]->next_time->lock) {
          dbg ("Problem with key[%s] timeout = %d\n", time_st[i]->next_time->name,
               time_st[i]->next_time->timeout);
        }
        assert (!time_st[i]->next_time->lock);
//        fprintf (stderr, "delete qkey\n");
        delete_qkey (time_st[i]->next_time);
      }
      qkey_free (time_st[i]);
    }
    assert (keys_cnt == 0);

//    fprintf (stderr, "qs = %p %ld\n", qs, sizeof (queue));
    while (qs != NULL) {
      queue *q = qs;
      qs = (queue *)qs->ev_first;
      dl_free (q, sizeof (queue));
    }

    shmap_string_vptr_free (&h_queue);
    shmap_string_vptr_free (&h_qkey);
    map_int_int_free (&secrets);
    map_ll_vptr_free (&alias);

    hset_llp_free (&h_subscribers);

    dl_crypto_free (&cr);

    long long left_memory = dl_get_memory_used() - treap_get_memory();

    fprintf (stderr, "Memory left: %lld\n", left_memory);
    assert (left_memory == 0);
  }
}