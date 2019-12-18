#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_3__ {int block_count; unsigned char** blocks; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ svn_bit_array__t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int BLOCK_SIZE ; 
 int BLOCK_SIZE_BITS ; 
 void* apr_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char**,unsigned char**,int) ; 
 int select_data_size (int) ; 

void
svn_bit_array__set(svn_bit_array__t *array,
                   apr_size_t idx,
                   svn_boolean_t value)
{
  unsigned char *block;

  /* Index within ARRAY->BLOCKS for the block containing bit IDX. */
  apr_size_t block_idx = idx / BLOCK_SIZE_BITS;

  /* Within that block, index of the byte containing IDX. */
  apr_size_t byte_idx = (idx % BLOCK_SIZE_BITS) / 8;

  /* Within that byte, index of the bit corresponding to IDX. */
  apr_size_t bit_idx = (idx % BLOCK_SIZE_BITS) % 8;

  /* If IDX is outside the allocated range, we _may_ have to grow it.
   *
   * Be sure to use division instead of multiplication as we need to cover
   * the full value range of APR_SIZE_T for the bit indexes.
   */
  if (block_idx >= array->block_count)
    {
      apr_size_t new_count;
      unsigned char **new_blocks;

      /* Unallocated indexes are implicitly 0, so no actual allocation
       * required in that case.
       */
      if (!value)
        return;

      /* Grow block list to cover IDX.
       * Clear the new entries to guarantee our array[idx]==0 default.
       */
      new_count = select_data_size(idx);
      new_blocks = apr_pcalloc(array->pool, new_count * sizeof(*new_blocks));
      memcpy(new_blocks, array->blocks,
             array->block_count * sizeof(*new_blocks));
      array->blocks = new_blocks;
      array->block_count = new_count;
    }

  /* IDX is covered by ARRAY->BLOCKS now. */

  /* Get the block that contains IDX.  Auto-allocate it if missing. */
  block = array->blocks[block_idx];
  if (block == NULL)
    {
      /* Unallocated indexes are implicitly 0, so no actual allocation
       * required in that case.
       */
      if (!value)
        return;

      /* Allocate the previously missing block and clear it for our
       * array[idx] == 0 default. */
      block = apr_pcalloc(array->pool, BLOCK_SIZE);
      array->blocks[block_idx] = block;
    }

  /* Set / reset one bit.  Be sure to use unsigned shifts. */
  if (value)
    block[byte_idx] |=  (unsigned char)(1u << bit_idx);
  else
    block[byte_idx] &= ~(unsigned char)(1u << bit_idx);
}