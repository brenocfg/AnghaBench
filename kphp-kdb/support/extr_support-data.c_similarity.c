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

/* Variables and functions */
 double word_weight (int) ; 

double similarity (int *x, int *y, double *a, double *b) {
  *a = 0, *b = 0;

  int xi = 0, yi = 0;
  while (x[xi] || y[yi]) {
    if (x[xi] == y[yi]) {
      *a += 2.0 * word_weight (x[xi]);
      xi++;
      yi++;
    } else {
      if (x[xi] && (y[yi] == 0 || x[xi] < y[yi])) {
        *b += word_weight (x[xi]);
        xi++;
      } else {
        *b += word_weight (y[yi]);
        yi++;
      }
    }
  }

  if (*a + *b < 1e-9) {
    return -1.0;
  }
  return (*a - *b) * 1.0 / (*a + *b);
}