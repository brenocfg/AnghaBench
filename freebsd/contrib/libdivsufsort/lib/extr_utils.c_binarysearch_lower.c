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
typedef  int saidx_t ;

/* Variables and functions */

__attribute__((used)) static
saidx_t
binarysearch_lower(const saidx_t *A, saidx_t size, saidx_t value) {
  saidx_t half, i;
  for(i = 0, half = size >> 1;
      0 < size;
      size = half, half >>= 1) {
    if(A[i + half] < value) {
      i += half + 1;
      half -= (size & 1) ^ 1;
    }
  }
  return i;
}