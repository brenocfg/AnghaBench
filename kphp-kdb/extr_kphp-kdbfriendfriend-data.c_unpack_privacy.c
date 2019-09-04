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
#define  CAT_FR_ALL 130 
#define  CAT_FR_FR 129 
#define  CAT_FR_PACKED 128 
 int MAX_PRIVACY_LEN ; 
 int* P ; 
 int PL ; 
 int PL_M_CAT ; 
 int PL_M_MASK ; 
 int /*<<< orphan*/  assert (int) ; 

int unpack_privacy (const int *PP, int L) {
  const int *PE = PP + L;
  int *A = P;
  assert (L <= MAX_PRIVACY_LEN);
  while (PP < PE) {
    int x = *PP++, s;
    assert (A < P + MAX_PRIVACY_LEN - 32);
    if (!(x & PL_M_CAT)) {
      *A++ = x;
      continue;
    }
    s = x & ~PL_M_MASK;
    switch (x & PL_M_MASK) {
    case CAT_FR_ALL:
    case CAT_FR_FR:
      *A++ = x;
      continue;
    case CAT_FR_PACKED:
      *A++ = s;
      continue;
    }
    int i;
    for (i = 0; i < 30; i++) {
      if (x & 1) {
        *A++ = s + i + 1;
      }
      x >>= 1;
    }
  }
  *A = -1;
  PL = A - P;
  return PL;
}