#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ status; struct TYPE_13__* next; struct TYPE_13__* hnext; } ;
typedef  TYPE_1__ transaction_t ;
typedef  TYPE_1__ tlist_t ;
typedef  int /*<<< orphan*/  A ;

/* Variables and functions */
 TYPE_1__** H ; 
 int HASH_MASK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__ auto_running_list ; 
 TYPE_1__** calloc (int,int) ; 
 scalar_t__ check_is_running (TYPE_1__*) ; 
 int /*<<< orphan*/  cmp_transaction ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 int /*<<< orphan*/  qsort (TYPE_1__**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlist_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  tlist_insert (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  transaction_finish_execution (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ts_running ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 

int find_running_transactions (void) {
  int i, r = 0, t = 0;
  tlist_t terminated_list;
  tlist_clear (&terminated_list);
  transaction_t *P;
  for (i = 0; i <= HASH_MASK; i++) {
    for (P = H[i]; P != NULL; P = P->hnext) {
      if (P->status == ts_running) {
        if (check_is_running (P)) {
          vkprintf (4, "tlist_insert (&auto_running_list, %p)\n", P);
          tlist_insert (&auto_running_list, P);
          r++;
        } else {
          vkprintf (4, "tlist_insert (&auto_terminated_list, %p)\n", P);
          tlist_insert (&terminated_list, P);
          t++;
        }
      }
    }
  }

  if (t > 0) {
    transaction_t **A = calloc (t, sizeof (A[0]));
    assert (A != NULL);
    for (P = terminated_list.next, i = 0; P != &terminated_list; P = P->next) {
      A[i++] = P;
    }
    qsort (A, t, sizeof (A[0]), cmp_transaction);
    for (i = 0; i < t; i++) {
      vkprintf (4, "find_running_transactions: call transaction_finish_execution\n");
      transaction_finish_execution (A[i], 0);
    }
    free (A);
    vkprintf (3, "found %d terminated transaction(s)\n", t);
  }

  return r;
}