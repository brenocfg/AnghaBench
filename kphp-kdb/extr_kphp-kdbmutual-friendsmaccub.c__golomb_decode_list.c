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
typedef  char const* golomb ;

/* Variables and functions */
 int LEN_BITS ; 
 int /*<<< orphan*/  assert (int) ; 
 int compute_golomb_parameter (int,int) ; 
 scalar_t__ cur_bit ; 
 int /*<<< orphan*/  load_bit () ; 

int _golomb_decode_list (golomb ptr, int tot_items, int bytes, int *P) {
  const char *end = ptr + bytes;

  int k = LEN_BITS, p = 1 << (LEN_BITS + 1);

  int m = ((int) *ptr++ << 24) + (1 << 23);

  int tmp = 0;
  while (k >= 0) {
    if (cur_bit) { tmp += (1 << k); }
    load_bit ();
    k--;
  }

  int len = tmp;
//  fprintf (stderr, "len = %d\n", len);

  //assert (len > 0 && bytes > 0);

  int a = tot_items + len + 1, M = compute_golomb_parameter (tot_items + len, len);
  k = 0, p = 1;
  while (M >= p) {
    p <<= 1;
    k++;
  }
  p -= M;

  while (len--) {
    int d = 0, i;
    while (cur_bit) {
      a -= M;
      load_bit();
    }
    load_bit();
    for (i = k; i > 1; i--) {
      d <<= 1;
      if (cur_bit) {
        d++;
      }
      load_bit();
    }
    if (d >= p) {
      d <<= 1;
      if (cur_bit) {
        d++;
      }
      load_bit();
      d -= p;
    }
    a -= d;
//    fprintf (stderr, "golomb decode: %d (delta=%d) %d\n", a, d, *P);
    assert (a == *P);
    P++;
  }
  if (m & (1 << 23)) { ptr--; }
  assert (ptr == end);

  return tmp;
#undef cur_bit
#undef load_bit
}