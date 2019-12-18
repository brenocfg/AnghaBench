#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int right; TYPE_1__* w; scalar_t__ left; } ;
typedef  TYPE_2__ pm_cell_t ;
struct TYPE_12__ {int* next; size_t choice; int /*<<< orphan*/ * freq; } ;
struct TYPE_10__ {int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREQ_INFTY ; 
 TYPE_5__* PB ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  pm_tree_advance (TYPE_2__*,TYPE_5__*) ; 
 int /*<<< orphan*/  pm_tree_advb (TYPE_2__*,TYPE_5__*) ; 
 int /*<<< orphan*/  pm_tree_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

void pm_huffman_build (pm_cell_t *A, int N) {
  int i;
  assert ((unsigned) N < (1 << 27) && N > 1); // we need -N .. 7*N to fit in int
  A += N;
  A[0].left = 0;	   // head of free cell list
  A[0].right = 15 * N;      // last available cell + 1
  PB[32].freq[0] = PB[32].freq[1] = FREQ_INFTY;
  // print_tree_builder (A, PB + 32);
  for (i = 31; i >= 0; i--) {
    PB[i].next[0] = -N;
    PB[i].freq[0] = A[-N].w->freq;
    pm_tree_advb (A, PB + i);
    // print_tree_builder (A, PB + i);
  }
  for (i = 2*N - 2; i > 0; i--) { /* do N-1 times */
    // print_tree_builder (A, PB);
    int n = PB->next[PB->choice];
    assert (n);
    // fprintf (stderr, "#%d:\t%lld\t", i, PB->freq[PB->choice]);
    pm_tree_free (A, n);
    // fprintf (stderr, "\n");
    pm_tree_advance (A, PB);
  }
  if (verbosity > 1) {
    fprintf (stderr, "package-merge: maximal memory usage is %d+%d 8-byte cells out of %d+%d\n", N, 15 * N - A[0].right, N, 15 * N);
  }
}