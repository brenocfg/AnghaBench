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
struct bookmark {int dummy; } ;

/* Variables and functions */
 scalar_t__ cmp_bookmark (struct bookmark*,struct bookmark*) ; 

__attribute__((used)) static void sort_bookmarks (struct bookmark *A, int b) {
  if (b <= 0) {
    return;
  }
  int i = 0, j = b;
  struct bookmark h = A[b >> 1], t;
  do {
    while (cmp_bookmark (A + i, &h) < 0) { i++; }
    while (cmp_bookmark (A + j, &h) > 0) { j--; }
    if (i <= j) {
      t = A[i];  A[i++] = A[j];  A[j--] = t;
    }
  } while (i <= j);
  sort_bookmarks (A + i, b - i);
  sort_bookmarks (A, j);
}