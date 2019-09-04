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
 scalar_t__ DUMP_DEBUG_INFO ; 
 scalar_t__ DUMP_ENDIAN_BIG ; 
 scalar_t__ DUMP_ENDIAN_NAT ; 
 scalar_t__ FLAG_BYTEORDER_NATIVE ; 

__attribute__((used)) static uint8_t
dump_flags(uint8_t flags, uint8_t native)
{
  if (native == FLAG_BYTEORDER_NATIVE) {
    if ((flags & DUMP_ENDIAN_NAT) == 0) {
      return (flags & DUMP_DEBUG_INFO) | DUMP_ENDIAN_NAT;
    }
    return flags;
  }
  if ((flags & DUMP_ENDIAN_NAT) == 0) {
    return (flags & DUMP_DEBUG_INFO) | DUMP_ENDIAN_BIG;
  }
  return flags;
}