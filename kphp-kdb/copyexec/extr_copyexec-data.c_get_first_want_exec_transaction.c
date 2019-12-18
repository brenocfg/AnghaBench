#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ binlog_pos; struct TYPE_5__* hnext; } ;
typedef  TYPE_1__ transaction_t ;

/* Variables and functions */
 TYPE_1__** H ; 
 int HASH_MASK ; 
 scalar_t__ transaction_want_exec (TYPE_1__*) ; 

__attribute__((used)) static transaction_t *get_first_want_exec_transaction (void) {
  int i;
  transaction_t *T = NULL, *U = NULL;
  for (i = 0; i <= HASH_MASK; i++) {
    transaction_t *P;
    for (P = H[i]; P != NULL; P = P->hnext) {
      if (transaction_want_exec (P)) {
        if (!T || T->binlog_pos > P->binlog_pos) {
          T = P;
        }
      } else {
        if (!U || U->binlog_pos < P->binlog_pos) {
          U = P;
        }
      }
    }
  }
  return T ? T : U;
}