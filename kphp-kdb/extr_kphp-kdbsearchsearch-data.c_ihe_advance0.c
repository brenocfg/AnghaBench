#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  y; int /*<<< orphan*/  item; struct TYPE_6__* right; } ;
typedef  TYPE_1__ tree_t ;
struct TYPE_7__ {int sp; int* Bt; int /*<<< orphan*/  cur0; int /*<<< orphan*/  cur_y; TYPE_1__** TS; } ;
typedef  TYPE_2__ iheap_en_t ;

/* Variables and functions */
 int MAX_TREE_DEPTH ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ihe_dive (TYPE_2__*) ; 
 int ihe_load (TYPE_2__*) ; 

__attribute__((used)) static int ihe_advance0 (iheap_en_t *A) {
  int sp = A->sp;
  tree_t *T;

  // fprintf (stderr, "ihe_advance(%p): sp=%d\n", A, sp);

  assert (A->cur0 && sp >= 0);

  T = A->TS[sp];

  do {
    if (!T->right) {
      sp = A->Bt[sp];
      if (sp < 0) {
        break;
      }
      T = A->TS[sp];
    } else {
      assert (sp < MAX_TREE_DEPTH-1);
      A->TS[++sp] = T->right;
      A->Bt[sp] = A->Bt[sp-1];
      A->sp = sp;

      if (ihe_dive(A) != 0) {
        sp = -1;
        break;
      }
      sp = A->sp;
      T = A->TS[sp];
    }
    A->cur0 = T->item;
    A->cur_y = T->y;
  } while (0);

  // fprintf (stderr, "ihe_adv() done, sp=%d, cur=%p (item_id=%016llx)\n", sp, sp < 0 ? 0 : A->cur, sp < 0 ? 0 : A->cur->item_id);

  if (sp < 0) {
    A->sp = -1;
    A->cur0 = 0;
    return ihe_load (A);
  }

  A->sp = sp;

  return ihe_load (A);
}