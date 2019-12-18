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
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int APR_SIZE_MAX ; 
 scalar_t__ SVN__STREAM_CHUNK_SIZE ; 

__attribute__((used)) static apr_size_t
optimimal_allocation_size(apr_size_t needed)
{
  /* For all allocations, assume some overhead that is shared between
   * OS memory managemnt, APR memory management and svn_stringbuf_t. */
  const apr_size_t overhead = 0x400;
  apr_size_t optimal;

  /* If an allocation size if safe for other ephemeral buffers, it should
   * be safe for ours. */
  if (needed <= SVN__STREAM_CHUNK_SIZE)
    return needed;

  /* Paranoia edge case:
   * Skip our heuristics if they created arithmetical overflow.
   * Beware to make this test work for NEEDED = APR_SIZE_MAX as well! */
  if (needed >= APR_SIZE_MAX / 2 - overhead)
    return needed;

  /* As per definition SVN__STREAM_CHUNK_SIZE is a power of two.
   * Since we know NEEDED to be larger than that, use it as the
   * starting point.
   *
   * Heuristics: Allocate a power-of-two number of bytes that fit
   *             NEEDED plus some OVERHEAD.  The APR allocator
   *             will round it up to the next full page size.
   */
  optimal = SVN__STREAM_CHUNK_SIZE;
  while (optimal - overhead < needed)
    optimal *= 2;

  /* This is above or equal to NEEDED. */
  return optimal - overhead;
}