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
typedef  int u32 ;

/* Variables and functions */
 char const* OPTI_STR_APPENDED_SALT ; 
 char const* OPTI_STR_BRUTE_FORCE ; 
 char const* OPTI_STR_EARLY_SKIP ; 
 char const* OPTI_STR_MEET_IN_MIDDLE ; 
 char const* OPTI_STR_NOT_ITERATED ; 
 char const* OPTI_STR_NOT_SALTED ; 
 char const* OPTI_STR_OPTIMIZED_KERNEL ; 
 char const* OPTI_STR_PRECOMPUTE_INIT ; 
 char const* OPTI_STR_PREPENDED_SALT ; 
 char const* OPTI_STR_RAW_HASH ; 
 char const* OPTI_STR_SINGLE_HASH ; 
 char const* OPTI_STR_SINGLE_SALT ; 
 char const* OPTI_STR_SLOW_HASH_SIMD_COMP ; 
 char const* OPTI_STR_SLOW_HASH_SIMD_INIT ; 
 char const* OPTI_STR_SLOW_HASH_SIMD_LOOP ; 
 char const* OPTI_STR_USES_BITS_16 ; 
 char const* OPTI_STR_USES_BITS_32 ; 
 char const* OPTI_STR_USES_BITS_64 ; 
 char const* OPTI_STR_USES_BITS_8 ; 
 char const* OPTI_STR_ZERO_BYTE ; 
#define  OPTI_TYPE_APPENDED_SALT 147 
#define  OPTI_TYPE_BRUTE_FORCE 146 
#define  OPTI_TYPE_EARLY_SKIP 145 
#define  OPTI_TYPE_MEET_IN_MIDDLE 144 
#define  OPTI_TYPE_NOT_ITERATED 143 
#define  OPTI_TYPE_NOT_SALTED 142 
#define  OPTI_TYPE_OPTIMIZED_KERNEL 141 
#define  OPTI_TYPE_PRECOMPUTE_INIT 140 
#define  OPTI_TYPE_PREPENDED_SALT 139 
#define  OPTI_TYPE_RAW_HASH 138 
#define  OPTI_TYPE_SINGLE_HASH 137 
#define  OPTI_TYPE_SINGLE_SALT 136 
#define  OPTI_TYPE_SLOW_HASH_SIMD_COMP 135 
#define  OPTI_TYPE_SLOW_HASH_SIMD_INIT 134 
#define  OPTI_TYPE_SLOW_HASH_SIMD_LOOP 133 
#define  OPTI_TYPE_USES_BITS_16 132 
#define  OPTI_TYPE_USES_BITS_32 131 
#define  OPTI_TYPE_USES_BITS_64 130 
#define  OPTI_TYPE_USES_BITS_8 129 
#define  OPTI_TYPE_ZERO_BYTE 128 

const char *stroptitype (const u32 opti_type)
{
  switch (opti_type)
  {
    case OPTI_TYPE_OPTIMIZED_KERNEL:    return OPTI_STR_OPTIMIZED_KERNEL;
    case OPTI_TYPE_ZERO_BYTE:           return OPTI_STR_ZERO_BYTE;
    case OPTI_TYPE_PRECOMPUTE_INIT:     return OPTI_STR_PRECOMPUTE_INIT;
    case OPTI_TYPE_MEET_IN_MIDDLE:      return OPTI_STR_MEET_IN_MIDDLE;
    case OPTI_TYPE_EARLY_SKIP:          return OPTI_STR_EARLY_SKIP;
    case OPTI_TYPE_NOT_SALTED:          return OPTI_STR_NOT_SALTED;
    case OPTI_TYPE_NOT_ITERATED:        return OPTI_STR_NOT_ITERATED;
    case OPTI_TYPE_PREPENDED_SALT:      return OPTI_STR_PREPENDED_SALT;
    case OPTI_TYPE_APPENDED_SALT:       return OPTI_STR_APPENDED_SALT;
    case OPTI_TYPE_SINGLE_HASH:         return OPTI_STR_SINGLE_HASH;
    case OPTI_TYPE_SINGLE_SALT:         return OPTI_STR_SINGLE_SALT;
    case OPTI_TYPE_BRUTE_FORCE:         return OPTI_STR_BRUTE_FORCE;
    case OPTI_TYPE_RAW_HASH:            return OPTI_STR_RAW_HASH;
    case OPTI_TYPE_SLOW_HASH_SIMD_INIT: return OPTI_STR_SLOW_HASH_SIMD_INIT;
    case OPTI_TYPE_SLOW_HASH_SIMD_LOOP: return OPTI_STR_SLOW_HASH_SIMD_LOOP;
    case OPTI_TYPE_SLOW_HASH_SIMD_COMP: return OPTI_STR_SLOW_HASH_SIMD_COMP;
    case OPTI_TYPE_USES_BITS_8:         return OPTI_STR_USES_BITS_8;
    case OPTI_TYPE_USES_BITS_16:        return OPTI_STR_USES_BITS_16;
    case OPTI_TYPE_USES_BITS_32:        return OPTI_STR_USES_BITS_32;
    case OPTI_TYPE_USES_BITS_64:        return OPTI_STR_USES_BITS_64;
  }

  return NULL;
}