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
struct pm_tree_builder {int* next; size_t choice; long long* freq; } ;
struct TYPE_4__ {int left; int right; } ;
typedef  TYPE_1__ pm_cell_t ;

/* Variables and functions */
 void* FREQ_INFTY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pm_tree_advance (TYPE_1__*,struct pm_tree_builder*) ; 

__attribute__((used)) static void pm_tree_advb (pm_cell_t *A, struct pm_tree_builder *B) {
  ++B;
  int n1 = B->next[B->choice];
  if (!n1) {
    --B;
    B->next[1] = 0;
    B->freq[1] = FREQ_INFTY;
    B->choice = 0;
    return;
  }
  long long f = B->freq[B->choice];
  pm_tree_advance (A, B);
  int n2 = B->next[B->choice];
  if (!n2) {
    --B;
    B->next[1] = 0;
    B->freq[1] = FREQ_INFTY;
    B->choice = 0;
    return;
  }
  f += B->freq[B->choice];
  pm_tree_advance (A, B);
  int n = A[0].left;
  if (n) {
    A[0].left = A[n].left;
  } else { /* no cells in free list */
    n = --A[0].right;
    assert (n && "Out of package-merge cell memory" != 0);
  }
  A[n].left = n1;
  A[n].right = n2;
  --B;
  B->next[1] = n;
  B->freq[1] = f;
  B->choice = (f < B->freq[0]);
}