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
struct bitwriter {int dummy; } ;

/* Variables and functions */
 int HUFFMAN_MAX_CODE_LENGTH ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bwrite_nbits (struct bitwriter*,int,int) ; 

void bwrite_huffman_codes (struct bitwriter *bw, int *l, int N) {
  int i;
  for (i = 0; i < N; i++) {
    assert (l[i] >= 0 && l[i] <= HUFFMAN_MAX_CODE_LENGTH);
    bwrite_nbits (bw, l[i], 4);
  }
}