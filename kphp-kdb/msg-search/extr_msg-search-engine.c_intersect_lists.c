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

int *intersect_lists (int *A, int *Ae, int *B, int *Be, int *D, int *De) {
  int x, *C = B;

  while (A < Ae) {
    x = *A++;
    if (x > 0) {
      while (B < Be && (unsigned) *B > (unsigned) x) B++;
      if (B == Be) continue;
      if (*B == x) {
	if (D < De) *D++ = x;
      }
    } else {
      while (C < Be && (unsigned) *C < (unsigned) x) C++;
      if (C == Be) continue;
      if (*C == x) {
	if (D < De) *D++ = x;
      }
    }
  }

  return D;
}