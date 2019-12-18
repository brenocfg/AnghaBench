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
typedef  scalar_t__ hash_t ;

/* Variables and functions */
 scalar_t__* HL ; 

__attribute__((used)) static void hsort (int a, int b) {
  int i, j;
  hash_t t, h;
  if (a >= b) { return; }
  i = a;  j = b;  h = HL[(a+b)>>1];
  do {
    while (HL[i] < h) { i++; }
    while (HL[j] > h) { j--; }
    if (i <= j) {
      t = HL[i];  HL[i++] = HL[j];  HL[j--] = t;
    }
  } while (i <= j);
  hsort (a, j);
  hsort (i, b);
}