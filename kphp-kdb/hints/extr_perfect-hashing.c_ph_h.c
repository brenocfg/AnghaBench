#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* sums; int* used; int /*<<< orphan*/  code; scalar_t__ d; int /*<<< orphan*/  mul1; int /*<<< orphan*/  mul0; } ;
typedef  TYPE_1__ perfect_hash ;

/* Variables and functions */
 scalar_t__ bits_cnt (int) ; 
 int get_bit (int /*<<< orphan*/ ,int) ; 
 int poly_h (long long,int /*<<< orphan*/ ,scalar_t__) ; 

int ph_h (perfect_hash *h, long long s) {
  int h0 = poly_h (s, h->mul0, h->d),
      h1 = poly_h (s, h->mul1, h->d);

  h1 += h->d;

  int i;
  if (get_bit (h->code, h0) ^ get_bit (h->code, h1)) {
    i = h1;
  } else {
    i = h0;
  }

//  int tt = i;

  int res = 0;//, j;
  res = h->sums[i >> 6];

  int left = (i & 63);
  i = (i >> 5) & -2;
  if (left >= 32) {
    res += bits_cnt (h->used[i++]);
    left -= 32;
  }

  res += bits_cnt (h->used[i] & ((1 << left) - 1));
/*
  int tres = 0;
  for (j = 0; j < tt; j++) {
    tres += get_bit (h->used, j);
  }
  fprintf (stderr, "%d : %d vs %d\n", tt, res, tres);
  assert (res == tres);
  */
  return res;
}