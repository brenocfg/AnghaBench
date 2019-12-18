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

__attribute__((used)) static
void
tr_partialcopy(int *ISA, const int *SA,
               int *first, int *a, int *b, int *last,
               int depth) {
  int *c, *d, *e;
  int s, v;
  int rank, lastrank, newrank = -1;

  v = b - SA - 1;
  lastrank = -1;
  for(c = first, d = a - 1; c <= d; ++c) {
    if((0 <= (s = *c - depth)) && (ISA[s] == v)) {
      *++d = s;
      rank = ISA[s + depth];
      if(lastrank != rank) { lastrank = rank; newrank = d - SA; }
      ISA[s] = newrank;
    }
  }

  lastrank = -1;
  for(e = d; first <= e; --e) {
    rank = ISA[*e];
    if(lastrank != rank) { lastrank = rank; newrank = e - SA; }
    if(newrank != rank) { ISA[*e] = newrank; }
  }

  lastrank = -1;
  for(c = last - 1, e = d + 1, d = b; e < d; --c) {
    if((0 <= (s = *c - depth)) && (ISA[s] == v)) {
      *--d = s;
      rank = ISA[s + depth];
      if(lastrank != rank) { lastrank = rank; newrank = d - SA; }
      ISA[s] = newrank;
    }
  }
}