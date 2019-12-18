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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int bsr (unsigned int) ; 
 int /*<<< orphan*/  bwrite_append (struct bitwriter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwrite_nbits (struct bitwriter*,unsigned int,int) ; 

void bwrite_gamma_code (struct bitwriter *bw, unsigned int d) {
  assert (d > 0);
  int i, k = bsr (d);
  d ^= 1U << k;
  for (i = 0; i < k; i++) {
    if (!bw->m) {
      bwrite_append (bw, 0);
      bw->m = 0x80;
    }
    *bw->ptr += bw->m;
    bw->m >>= 1;
  }
  if (!bw->m) {
    bwrite_append (bw, 0);
    bw->m = 0x80;
  }
  bw->m >>= 1;
  bwrite_nbits (bw, d, k);
}