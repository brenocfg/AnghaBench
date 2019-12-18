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

__attribute__((used)) static apr_uint32_t hash_func(apr_uint32_t sum)
{
  /* Since the adl32 checksum have a bad distribution for the 11th to 16th
     bits when used for our small block size, we add some bits from the
     other half of the checksum. */
  return sum ^ (sum >> 12);
}