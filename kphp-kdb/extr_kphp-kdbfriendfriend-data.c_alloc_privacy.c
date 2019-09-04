#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int y; int* List; } ;
typedef  TYPE_1__ privacy_t ;

/* Variables and functions */
 int* P ; 
 size_t PL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int lrand48 () ; 
 int /*<<< orphan*/  memcpy (int*,int*,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  privacy_nodes ; 
 int /*<<< orphan*/  stderr ; 
 size_t tot_privacy_len ; 
 int verbosity ; 
 TYPE_1__* zmalloc (int) ; 

privacy_t *alloc_privacy (void) {
  int len = PL, *A, sz;
  assert (P[PL] == -1);
  if (len >= 255) {
    len++;
  }

  sz = sizeof(privacy_t) + len*4 + 4;
  tot_privacy_len += PL;
  privacy_nodes++;

  privacy_t *T = zmalloc (sz);
  memset (T, 0, sizeof(privacy_t));
  T->y = (lrand48() << 8) + (len >= 255 ? 255 : len);
  A = T->List;
  if (len >= 255) {
    *A++ = PL;
  }

  memcpy (A, P, (PL+1)*4);

  if (verbosity > 2) {
    fprintf (stderr, "in-core privacy: ");
    for (sz = 0; sz <= PL; sz++) {
      fprintf (stderr, " %08x", A[sz]);
    }
    fprintf (stderr, "\n");
  }

  return T;
}