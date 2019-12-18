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
typedef  int uint64_t ;

/* Variables and functions */
 int rand () ; 

__attribute__((used)) static inline uint64_t
_mum_next_factor (void) {
  uint64_t start = 0;
  int i;

  for (i = 0; i < 8; i++)
    start = (start << 8) | rand() % 256;
  return start;
}