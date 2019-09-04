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
struct bitwriter {int m; int* ptr; } ;
struct list_encoder {int last; int M; int p; int k; struct bitwriter bw; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bwrite_append (struct bitwriter*,int) ; 

__attribute__((used)) static void golomb_encode_int (struct list_encoder *enc, int d) {
  struct bitwriter *bw = &enc->bw;
  int td = d;
  d -= enc->last;
  enc->last = td;
  assert (d > 0);
  d--;
// d = qM + r
// output: q ones, 1 zero
// if r < p:=2^k-M, output: r using k-1 digits
// if r >= 2^k-M, output: r + 2^k - M using k digits
  while (d >= enc->M) {
    if (!bw->m) {
      bwrite_append (bw, 0x80);
      bw->m = 0x40;
    } else {
      *bw->ptr += bw->m;
      bw->m >>= 1;
    }
    d -= enc->M;
  }
  if (!bw->m) {
    bwrite_append (bw, 0);
    bw->m = 0x40;
  } else {
    bw->m >>= 1;
  }
  if (d < enc->p) {
    d = ((4*d + 2) << enc->k);
  } else {
    d = ((2*(d + enc->p) + 1) << enc->k);
  }
  while (d != (-1 << 31)) {
    if (!bw->m) {
      bwrite_append (bw, 0);
      bw->m = 0x80;
    }
    if (d < 0) { *bw->ptr += bw->m; }
    d <<= 1;
    bw->m >>= 1;
  }
}