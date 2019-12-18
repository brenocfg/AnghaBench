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
typedef  void* uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline void store32( void *dst, uint32_t w )
{
#if defined(NATIVE_LITTLE_ENDIAN) && !defined(HAVE_ALIGNED_ACCESS_REQUIRED)
  *( uint32_t * )( dst ) = w;
#else
  uint8_t *p = ( uint8_t * )dst;
  *p++ = ( uint8_t )w; w >>= 8;
  *p++ = ( uint8_t )w; w >>= 8;
  *p++ = ( uint8_t )w; w >>= 8;
  *p++ = ( uint8_t )w;
#endif
}