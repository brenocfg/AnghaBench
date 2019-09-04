#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int left; int right; TYPE_1__* w; } ;
typedef  TYPE_2__ pm_cell_t ;
struct TYPE_4__ {int /*<<< orphan*/  code_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void pm_tree_free (pm_cell_t *A, int n) {
  assert (n);
  if (n < 0) {
    A[n].w->code_len++;
    // fprintf (stderr, "%d[%d]", n, A[n].w->code_len);
  } else {
    // fprintf (stderr, "%d:(", n);
    pm_tree_free (A, A[n].left);
    // fprintf (stderr, " ");
    pm_tree_free (A, A[n].right);
    // fprintf (stderr, ")");
    A[n].left = A[0].left;
    A[0].left = n;
  }
}