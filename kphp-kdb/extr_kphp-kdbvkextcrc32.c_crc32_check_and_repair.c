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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 unsigned int compute_crc32 (void*,int) ; 
 int find_corrupted_bit (int,unsigned int const) ; 
 int repair_bit (void*,int,int) ; 

int crc32_check_and_repair (void *input, int l, unsigned *input_crc32, int force_exit) {
  unsigned computed_crc32 = compute_crc32 (input, l);
  const unsigned crc32_diff = computed_crc32 ^ (*input_crc32);
  if (!crc32_diff) {
    return 0;
  }
  int k = find_corrupted_bit (l, crc32_diff);
//  vkprintf (3, "find_corrupted_bit returns %d.\n", k);
  int r = repair_bit (input, l, k);
//  vkprintf (3, "repair_bit returns %d.\n", r);
  if (!r) {
    assert (compute_crc32 (input, l) == *input_crc32);
    if (force_exit) {
//      kprintf ("crc32_check_and_repair successfully repair one bit in %d bytes block.\n", l);
    }
    return 1;
  }
  if (!(crc32_diff & (crc32_diff - 1))) { /* crc32_diff is power of 2 */
    *input_crc32 = computed_crc32;
    if (force_exit) {
//      kprintf ("crc32_check_and_repair successfully repair one bit in crc32 (%d bytes block).\n", l);
    }
    return 2;
  }
  assert (!force_exit);
  *input_crc32 = computed_crc32;
  return -1;
}