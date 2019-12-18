#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int a; int len; int k; int p; int m; int M; int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_1__ golomb_iterator ;
typedef  int /*<<< orphan*/ * golomb ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int compute_golomb_parameter (int,int) ; 
 scalar_t__ cur_bit ; 
 int /*<<< orphan*/  golomb_iter_next (TYPE_1__*) ; 
 int /*<<< orphan*/  load_bit () ; 

void golomb_iter_init (golomb_iterator *it, golomb x, int tot_items, int len, int r) {
  it->ptr = x;

  if (x == NULL) {
    it->a = 0;
    it->len = 0;
    return;
  }

  it->k = -1;
  it->p = 1;

  while (it->p < tot_items) {
    it->p += it->p;
    it->k++;
  }

  it->m = ((int) *(it->ptr)++ << 24) + (1 << 23);

  int tmp = 0;
  while (it->k >= 0) {
    if (cur_bit) { tmp += (1 << it->k); }
    load_bit ();
    it->k--;
  }

  it->len = tmp + 1;

  assert (it->len > 0);

  it->a = tot_items + 1;
  it->M = compute_golomb_parameter (tot_items, it->len);

  it->k = 0, it->p = 1;
  while (it->M >= it->p) {
    it->p <<= 1;
    it->k++;
  }
  it->p -= it->M;

  golomb_iter_next (it);

  while (it->a > r) {
    golomb_iter_next (it);
  }
}