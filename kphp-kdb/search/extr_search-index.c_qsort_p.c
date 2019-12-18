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
struct TYPE_3__ {scalar_t__ word; scalar_t__ doc_id; } ;
typedef  TYPE_1__ pair_t ;

/* Variables and functions */
 TYPE_1__* P ; 

__attribute__((used)) static void qsort_p (int a, int b) {
  int i, j;
  pair_t h, t;
  if (a >= b) { return; }
  h = P[(a+b)>>1];
  i = a;
  j = b;
  do {
    while (P[i].word < h.word || (P[i].word == h.word && P[i].doc_id < h.doc_id)) { i++; }
    while (P[j].word > h.word || (P[j].word == h.word && P[j].doc_id > h.doc_id)) { j--; }
    if (i <= j) {
      t = P[i];  P[i++] = P[j];  P[j--] = t;
    }
  } while (i <= j);
  qsort_p (a, j);
  qsort_p (i, b);
}