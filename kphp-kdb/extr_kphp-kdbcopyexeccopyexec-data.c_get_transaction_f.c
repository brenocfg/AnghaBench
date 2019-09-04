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
struct TYPE_4__ {int transaction_id; struct TYPE_4__* hnext; } ;
typedef  TYPE_1__ transaction_t ;

/* Variables and functions */
 void** H ; 
 int HASH_MASK ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 int /*<<< orphan*/  tot_memory_transactions ; 

transaction_t *get_transaction_f (int id, int force) {
  int h = id & HASH_MASK;
  transaction_t **p = &(H[h]), *q;
  while (1) {
    q = *p;
    if (q == NULL) {
      break;
    }
    if (q->transaction_id == id) {
      *p = q->hnext;
      if (force >= 0) {
        q->hnext = H[h];
        H[h] = q;
      }
      return q;
    }
    p = &(q->hnext);
  }
  if (force > 0) {
    //q = zmalloc0 (sizeof (transaction_t));
    q = calloc (1, sizeof (transaction_t));
    if (q == NULL) {
      kprintf ("get_transaction_f: calloc returns NULL. %m\n");
      return NULL;
    }
    tot_memory_transactions++;
    q->transaction_id = id;
    q->hnext = H[h];
    H[h] = q;
    return q;
  }
  return NULL;
}