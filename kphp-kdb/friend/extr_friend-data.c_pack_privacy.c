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
 int CAT_FR_FR ; 
 int CAT_FR_PACKED ; 
 int* P ; 
 int PL_M_CAT ; 
 int PL_M_MASK ; 
 int* Q ; 
 int QL ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int pack_privacy (void) {
  int *A = P, *B = Q;
  while (*A != -1) {
    int x = *A++;
    if ((x & PL_M_CAT) && (x & PL_M_MASK) < CAT_FR_FR) {
      if (!(x & 0x1f)) {
        *B++ = (x & ~PL_M_MASK) | CAT_FR_PACKED;
        continue;
      }
      int m = 0, s = x;
      while (1) {
        m |= (1 << ((x & 0x1f) - 1));
        x = *A;
        if (x == -1 || ((s ^ x) < 0) || !(x & PL_M_CAT) || (x & PL_M_MASK) >= CAT_FR_FR || !(x & 0x1f)) {
          break;
        }
        A++;
      }
      x = s & ~PL_M_MASK;
      m &= PL_M_MASK;
      if (m >= CAT_FR_PACKED) {
        *B++ = x + (m & 0xffff);
        m &= -0x10000;
      }
      x |= m;
    }
    *B++ = x;
  }
  QL = B - Q;

  if (verbosity > 2) {
    int i;
    fprintf (stderr, "packed privacy: ");
    for (i = 0; i < QL; i++) {
      fprintf (stderr, " %08x", Q[i]);
    }
    fprintf (stderr, "\n");
  }

  return QL;
}