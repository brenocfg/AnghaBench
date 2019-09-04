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
struct TYPE_3__ {int* head; int* value; int* prev; } ;
typedef  TYPE_1__ buckets_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void ss_bucket_sort (buckets_t *B, int *p, int n, int *R, int k) {
  int i, j, r;
  for (i = -1; i < n; i++) {
    B->head[i] = -1;
  }
  for (r = 0; r < n; r++) {
    j = p[r] + k;
    i = (j < n) ? R[j] : -1;
    B->value[r] = p[r];
    B->prev[r] = B->head[i];
    B->head[i] = r;
  }
  r = n - 1;
  for (i = n - 1; i >= -1; i--) {
    for (j = B->head[i]; j >= 0; j = B->prev[j]) {
      p[r] = B->value[j];
      r--;
    }
  }
  assert (r == -1);
}