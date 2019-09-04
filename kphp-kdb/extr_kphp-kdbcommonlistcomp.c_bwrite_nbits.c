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
 int /*<<< orphan*/  bwrite_append (struct bitwriter*,int /*<<< orphan*/ ) ; 

void bwrite_nbits (struct bitwriter *bw, unsigned int d, int n) {
  assert (!(n & -32));
  if (!n) { return; }
  unsigned int i;
  for (i = 1U << (n-1); i != 0; i >>= 1) {
    if (!bw->m) {
      bwrite_append (bw, 0);
      bw->m = 0x80;
    }
    if (d & i) {
      *bw->ptr += bw->m;
    }
    bw->m >>= 1;
  }
}