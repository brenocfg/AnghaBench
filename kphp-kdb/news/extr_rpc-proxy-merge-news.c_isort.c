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
struct TYPE_3__ {int date; } ;
typedef  TYPE_1__ item_t ;

/* Variables and functions */
 TYPE_1__** X ; 

void isort (int a, int b) {
  int i, j, h;
  item_t *t;
  if (a >= b) { return; }
  i = a;  j = b;  h = X[(a+b)>>1]->date;
  do {
    while (X[i]->date > h) { i++; }
    while (X[j]->date < h) { j--; }
    if (i <= j) {
      t = X[i];  X[i++] = X[j];  X[j--] = t;
    }
  } while (i <= j);
  isort (a, j);
  isort (i, b);
}