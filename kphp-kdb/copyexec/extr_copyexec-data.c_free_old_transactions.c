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
struct TYPE_4__ {long long binlog_pos; scalar_t__ status; struct TYPE_4__* hnext; } ;
typedef  TYPE_1__ transaction_t ;

/* Variables and functions */
 TYPE_1__** H ; 
 int HASH_MASK ; 
 int /*<<< orphan*/  transaction_free (TYPE_1__*) ; 
 scalar_t__ ts_running ; 

__attribute__((used)) static void free_old_transactions (long long start_pos) {
  int i;
  for (i = 0; i <= HASH_MASK; i++) {
    transaction_t *head = NULL, *tail = NULL, *P, *W;
    for (P = H[i]; P != NULL; P = W) {
      W = P->hnext;
      if (P->binlog_pos >= start_pos || P->status == ts_running) {
        P->hnext = NULL;
        if (head) {
          tail->hnext = P;
          tail = P;
        } else {
          head = tail = P;
        }
      } else {
        transaction_free (P);
      }
    }
    H[i] = head;
  }
}