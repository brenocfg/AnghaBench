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
typedef  int /*<<< orphan*/  voting_t ;

/* Variables and functions */
 scalar_t__ cmp_voting (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sort_votings (voting_t *A, int b) {
  if (b <= 0) {
    return;
  }
  int i = 0, j = b;
  voting_t h = A[b >> 1], t;
  do {
    while (cmp_voting (&A[i], &h) < 0) { i++; }
    while (cmp_voting (&h, &A[j]) < 0) { j--; }
    if (i <= j) {
      t = A[i];  A[i++] = A[j];  A[j--] = t;
    }
  } while (i <= j);
  sort_votings (A + i, b - i);
  sort_votings (A, j);
}