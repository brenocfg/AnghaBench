#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct transaction {int dummy; } ;
struct account {int trans_alloc; int trans_num; struct transaction** acc_transactions; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct transaction**,struct transaction**,int) ; 
 int /*<<< orphan*/  zfree (struct transaction**,int) ; 
 void* zmalloc (int) ; 

__attribute__((used)) static int add_acc_transaction (struct account *A, struct transaction *T) {
  if (!A->trans_alloc) {
    A->trans_alloc = 8;
    A->acc_transactions = zmalloc (8 * sizeof (void *));
  }
  if (A->trans_num == A->trans_alloc) {
    struct transaction **N = zmalloc ((A->trans_alloc << 1) * sizeof (void *));
    memcpy (N, A->acc_transactions, A->trans_alloc * sizeof (void *));
    zfree (A->acc_transactions, A->trans_alloc * sizeof (void *));
    A->acc_transactions = N;
    A->trans_alloc <<= 1;
  }

  A->acc_transactions[A->trans_num++] = T;
  return A->trans_num;
}