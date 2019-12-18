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
typedef  int /*<<< orphan*/  golomb ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int compute_golomb_parameter (int,int) ; 
 int /*<<< orphan*/  golomb_decode_list (int /*<<< orphan*/ ,int,int,int*) ; 

int golomb_encode_list (int *P, int len, int tot_items, unsigned char *res) {
  assert (len > 0);

  int k = -1, p = 1;
  while (p < tot_items) {
    p += p;
    k++;
  }

  int m = 0x80;
  unsigned char *ptr = res;
  *ptr = 0;

  int tmp = len - 1;
  while (k >= 0) {
    if (!m) { *++ptr = 0; m = 0x80; }
    if ((tmp >> k) & 1) { *ptr += m; }
    m >>= 1;
    k--;
  }

  int M = compute_golomb_parameter (tot_items, len);

  k = 31, p = 1;
  while (p <= M) {
    p += p;
    k--;
  }
  p -= M;

  int a = tot_items + 1, d;

  while (len > 0) {
    len--;
    d = a - *P;
    a -= d;
//    fprintf (stderr, "golomb encode: %d (delta = %d)\n", a, d-1);
    P++;
    assert (d > 0);
    d--;
// d = qM + r
// output: q ones, 1 zero
// if r < p:=2^k-M, output: r using k-1 digits
// if r >= 2^k-M, output: r + 2^k - M using k digits
    while (d >= M) {
      if (!m) { *++ptr = 0x80;  m = 0x40; }
      else { *ptr += m;  m >>= 1; }
      d -= M;
    }
    if (!m) { *++ptr = 0;  m = 0x40; }
    else { m >>= 1; }
    if (d < p) {
      d = ((4*d + 2) << k);
    } else {
      d = ((2*(d + p) + 1) << k);
    }
    while (d != (-1 << 31)) {
      if (!m) { *++ptr = 0; m = 0x80; }
      if (d < 0) { *ptr += m; }
      d <<= 1;
      m >>= 1;
    }
  }
  if (m != 0x80) { ptr++; }
  a = ptr - res;
/*
  if (verbosity > 1) {
    fprintf (stderr, "%d bytes output\n", a);
    for (d = 0; d < a; d++) {
      fprintf (stderr, "%02x", (unsigned char) res[d]);
    }
    fprintf (stderr, "\n");
  }
*/
  golomb_decode_list ((golomb)res, tot_items, a, P - tmp - 1);

  return a;
}