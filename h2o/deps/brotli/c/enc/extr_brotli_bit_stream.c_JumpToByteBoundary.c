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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */

__attribute__((used)) static void JumpToByteBoundary(size_t* storage_ix, uint8_t* storage) {
  *storage_ix = (*storage_ix + 7u) & ~7u;
  storage[*storage_ix >> 3] = 0;
}