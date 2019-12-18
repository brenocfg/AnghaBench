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
typedef  scalar_t__ sauchar_t ;
typedef  scalar_t__ saint_t ;
typedef  size_t saidx_t ;

/* Variables and functions */

__attribute__((used)) static
int
_compare(const sauchar_t *T, saidx_t Tsize,
         const sauchar_t *P, saidx_t Psize,
         saidx_t suf, saidx_t *match) {
  saidx_t i, j;
  saint_t r;
  for(i = suf + *match, j = *match, r = 0;
      (i < Tsize) && (j < Psize) && ((r = T[i] - P[j]) == 0); ++i, ++j) { }
  *match = j;
  return (r == 0) ? -(j != Psize) : r;
}