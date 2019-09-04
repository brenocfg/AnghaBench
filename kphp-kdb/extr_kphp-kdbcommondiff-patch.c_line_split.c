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
struct TYPE_4__ {int offset; int length; } ;
typedef  TYPE_1__ diff_string_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* zmalloc (int) ; 

__attribute__((used)) static int line_split (unsigned char *a, int n, diff_string_t **R) {
  int i, k = 0;
  for (i = 0; i < n; i++) {
    if (a[i] == '\n') {
      k++;
    }
  }
  diff_string_t *A = zmalloc ((k + 1) * sizeof (diff_string_t));
  int first = 0, l = 0;
  for (i = 0; i < n - 1; i++) {
    if (a[i] == '\n') {
      A[l].offset = first;
      A[l].length = i - first + 1;
      l++;
      first = i + 1;
    }
  }
  A[l].offset = first;
  A[l].length = n - first;
  l++;
  assert (l <= k + 1);
  *R = A;
#ifdef DIFF_DEBUG
  for (k = 0; k < l; k++) {
    assert (!k || A[k-1].offset + A[k-1].length == A[k].offset);
    n -= A[k].length;
  }
  assert (!n);
#endif
  return l;
}