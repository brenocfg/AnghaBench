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
typedef  unsigned char svn_boolean_t ;
struct TYPE_3__ {int block_count; unsigned char** blocks; } ;
typedef  TYPE_1__ svn_bit_array__t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int BLOCK_SIZE_BITS ; 

svn_boolean_t
svn_bit_array__get(svn_bit_array__t *array,
                   apr_size_t idx)
{
  unsigned char *block;

  /* Index within ARRAY->BLOCKS for the block containing bit IDX. */
  apr_size_t block_idx = idx / BLOCK_SIZE_BITS;

  /* Within that block, index of the byte containing IDX. */
  apr_size_t byte_idx = (idx % BLOCK_SIZE_BITS) / 8;

  /* Within that byte, index of the bit corresponding to IDX. */
  apr_size_t bit_idx = (idx % BLOCK_SIZE_BITS) % 8;

  /* Indexes outside the allocated range are implicitly 0. */
  if (block_idx >= array->block_count)
    return 0;

  /* Same if the respective block has not been allocated. */
  block = array->blocks[block_idx];
  if (block == NULL)
    return 0;

  /* Extract one bit (get the byte, shift bit to LSB, extract it). */
  return (block[byte_idx] >> bit_idx) & 1;
}