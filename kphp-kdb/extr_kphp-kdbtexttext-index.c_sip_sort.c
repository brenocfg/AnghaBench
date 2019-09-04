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
struct search_index_pair {int dummy; } ;

/* Variables and functions */
 scalar_t__ sip_cmp (struct search_index_pair*,struct search_index_pair*) ; 

void sip_sort (struct search_index_pair *A, int b) {
  int i = 0, j = b;
  struct search_index_pair h, t;
  if (b <= 0) { return; }
  h = A[b >> 1];
  do {
    while (sip_cmp (&A[i], &h) < 0) { i++; }
    while (sip_cmp (&A[j], &h) > 0) { j--; }
    if (i <= j) {
      t = A[i];  A[i++] = A[j];  A[j--] = t;
    }
  } while (i <= j);
  sip_sort (A+i, b-i);
  sip_sort (A, j);
}