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
 scalar_t__* Q ; 
 int Qw ; 

int search_in_msg (hash_t *H, int hc) {
  int i, a, b, c;
  // fprintf (stderr, "have %d hashes in this msg: %llu, %llu, ...\n", hc, H[0], H[1]);
  for (i = 0; i < Qw; i++) {
    hash_t h = Q[i];
    a = -1;  b = hc;
    while (b - a > 1) {
      c = (a + b) >> 1;
      if (H[c] > h) { b = c; } else { a = c; }
    }
    if (a < 0 || H[a] != h) { return 0; }
  }
  return 1;
}