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
 int __builtin_clzll (unsigned long long) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void convert_words_list (unsigned long long *A, int N, int q) {
  if (N <= 0) {
    return;
  }
  int k = (N - 1) >> 1;
  unsigned long long u = ((q & 1) && !k ? -1LL : A[k] ^ A[k-1]);
  unsigned long long v = ((q & 2) && N == 1 ? -1LL : A[k] ^ A[k+1]);
  int need_bits = __builtin_clzll (u < v ? u : v) + 1;
  int skip_bits = __builtin_clzll (A[-1] ^ A[N]);

//  if (verbosity > 3) {
//    fprintf (stderr, "k=%d N=%d A[-1]=%016llx A[k-1]=%016llx A[k]=%016llx A[k+1]=%016llx A[N]=%016llx need=%d skip=%d\n",
//      k, N, A[-1], A[k-1], A[k], A[k+1], A[N], need_bits, skip_bits);
//  }

  convert_words_list (A, k, q & 1);
  convert_words_list (A + k + 1, N - k - 1, q & 2);

  assert (need_bits >= skip_bits && need_bits <= skip_bits + 58);

  A[k] &= (-1LL << (64 - need_bits));
  A[k] <<= skip_bits;
  A[k] |= need_bits - skip_bits;
}