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
typedef  int apr_size_t ;

/* Variables and functions */
 int BLOCK_SIZE_BITS ; 
 int INITIAL_BLOCK_COUNT ; 

__attribute__((used)) static apr_size_t
select_data_size(apr_size_t max)
{
  /* We allocate a power of two of bytes but at least 16 blocks. */
  apr_size_t size = INITIAL_BLOCK_COUNT;

  /* Caution:
   * MAX / BLOCK_SIZE_BITS == SIZE still means that MAX is out of bounds.
   * OTOH, 2 * (MAX/BLOCK_SIZE_BITS) is always within the value range of
   * APR_SIZE_T. */
  while (size <= max / BLOCK_SIZE_BITS)
    size *= 2;

  return size;
}