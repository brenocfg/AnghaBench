#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int n; unsigned char* y; int* p; int* lcp; } ;
typedef  TYPE_1__ suffix_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void suffix_array_check (suffix_array_t *A) {
  int i;
  for (i = 0; i + 1 < A->n; i++) {
    unsigned char *s = A->y + A->p[i];
    unsigned char *t = A->y + A->p[i+1];
    int o, l = A->n - A->p[i+1];
    if (l > A->n - A->p[i]) {
      l = A->n - A->p[i];
    }
    for (o = 0; o < l; o++) {
      if (*s != *t) { break; }
      s++;
      t++;
    }
    assert (s == A->y + A->n || *s < *t);
    assert (o == A->lcp[i+1]);
  }
  assert (A->lcp[0] == 0);
  assert (A->lcp[A->n] == 0);
}