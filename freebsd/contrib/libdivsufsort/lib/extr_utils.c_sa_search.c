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
typedef  int /*<<< orphan*/  sauchar_t ;
typedef  scalar_t__ saint_t ;
typedef  scalar_t__ saidx_t ;

/* Variables and functions */
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 scalar_t__ _compare (int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/  const*,scalar_t__,scalar_t__ const,scalar_t__*) ; 

saidx_t
sa_search(const sauchar_t *T, saidx_t Tsize,
          const sauchar_t *P, saidx_t Psize,
          const saidx_t *SA, saidx_t SAsize,
          saidx_t *idx) {
  saidx_t size, lsize, rsize, half;
  saidx_t match, lmatch, rmatch;
  saidx_t llmatch, lrmatch, rlmatch, rrmatch;
  saidx_t i, j, k;
  saint_t r;

  if(idx != NULL) { *idx = -1; }
  if((T == NULL) || (P == NULL) || (SA == NULL) ||
     (Tsize < 0) || (Psize < 0) || (SAsize < 0)) { return -1; }
  if((Tsize == 0) || (SAsize == 0)) { return 0; }
  if(Psize == 0) { if(idx != NULL) { *idx = 0; } return SAsize; }

  for(i = j = k = 0, lmatch = rmatch = 0, size = SAsize, half = size >> 1;
      0 < size;
      size = half, half >>= 1) {
    match = MIN(lmatch, rmatch);
    r = _compare(T, Tsize, P, Psize, SA[i + half], &match);
    if(r < 0) {
      i += half + 1;
      half -= (size & 1) ^ 1;
      lmatch = match;
    } else if(r > 0) {
      rmatch = match;
    } else {
      lsize = half, j = i, rsize = size - half - 1, k = i + half + 1;

      /* left part */
      for(llmatch = lmatch, lrmatch = match, half = lsize >> 1;
          0 < lsize;
          lsize = half, half >>= 1) {
        lmatch = MIN(llmatch, lrmatch);
        r = _compare(T, Tsize, P, Psize, SA[j + half], &lmatch);
        if(r < 0) {
          j += half + 1;
          half -= (lsize & 1) ^ 1;
          llmatch = lmatch;
        } else {
          lrmatch = lmatch;
        }
      }

      /* right part */
      for(rlmatch = match, rrmatch = rmatch, half = rsize >> 1;
          0 < rsize;
          rsize = half, half >>= 1) {
        rmatch = MIN(rlmatch, rrmatch);
        r = _compare(T, Tsize, P, Psize, SA[k + half], &rmatch);
        if(r <= 0) {
          k += half + 1;
          half -= (rsize & 1) ^ 1;
          rlmatch = rmatch;
        } else {
          rrmatch = rmatch;
        }
      }

      break;
    }
  }

  if(idx != NULL) { *idx = (0 < (k - j)) ? j : i; }
  return k - j;
}