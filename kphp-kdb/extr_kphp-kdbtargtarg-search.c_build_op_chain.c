#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* last; struct TYPE_6__* right; struct TYPE_6__* left; } ;
typedef  TYPE_1__ query_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* new_qnode (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relax_max_res (TYPE_1__*) ; 

query_t *build_op_chain (int op, query_t **QA, int N) {
  assert (N >= 2);
  query_t *Q, *R, *P = new_qnode (op, 0);
  P->left = QA[N-2];
  P->right = QA[N-1];
  relax_max_res (P);
  Q = P;
  N -= 2;
  while (N) {
    R = new_qnode (op, 0);
    R->left = QA[--N];
    R->right = Q;
    Q = R;
    relax_max_res (Q);
  }
  Q->last = P;
  return Q;
}