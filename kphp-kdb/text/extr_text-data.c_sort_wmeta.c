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
typedef  int /*<<< orphan*/  hash_t ;

/* Variables and functions */
 int* QL ; 
 unsigned char** QW_mfile ; 
 int* QW_msize ; 
 int /*<<< orphan*/ * QWords ; 

__attribute__((used)) static void sort_wmeta (int a, int b) {
  if (a >= b) {
    return;
  }
  int i = a, j = b, h = QL[(a+b)>>1];
  do {
    while (QL[i] < h) { i++; }
    while (QL[j] > h) { j--; }
    if (i <= j) {
      int t = QL[i];
      QL[i] = QL[j];
      QL[j] = t;
      t = QW_msize[i];
      QW_msize[i] = QW_msize[j];
      QW_msize[j] = t;
      unsigned char *tp = QW_mfile[i];
      QW_mfile[i] = QW_mfile[j];
      QW_mfile[j] = tp;
      hash_t tt;
      tt = QWords[i];
      QWords[i] = QWords[j];
      QWords[j] = tt;
      i++;
      j--;
    }
  } while (i <= j);
  sort_wmeta (a, j);
  sort_wmeta (i, b);
}