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
typedef  int apr_uint32_t ;

/* Variables and functions */
 int FLAGS_COUNT ; 

__attribute__((used)) static apr_uint32_t hash_flags(apr_uint32_t sum)
{
  /* The upper half of SUM has a wider value range than the lower 16 bit.
     Also, we want to a different folding than HASH_FUNC to minimize
     correlation between different hash levels. */
  return (sum >> 16) & ((FLAGS_COUNT / 8) - 1);
}