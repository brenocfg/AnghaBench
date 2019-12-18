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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  _mum_bswap64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint64_t
_mum_le (uint64_t v) {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ || !defined(MUM_TARGET_INDEPENDENT_HASH)
  return v;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
  return _mum_bswap64 (v);
#else
#error "Unknown endianess"
#endif
}