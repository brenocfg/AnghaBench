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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 size_t byte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  select_u8x4 (size_t*,size_t*,size_t*,size_t*,size_t const*,int) ; 
 int /*<<< orphan*/  word4 (size_t,size_t,size_t,size_t) ; 

__attribute__((used)) static uint32_t sub_word(uint32_t w, const uint8_t *sbox)
{
  uint8_t a = byte(w, 0),
          b = byte(w, 1),
          c = byte(w, 2),
          d = byte(w, 3);
#if CF_CACHE_SIDE_CHANNEL_PROTECTION
  select_u8x4(&a, &b, &c, &d, sbox, 256);
#else
  a = sbox[a];
  b = sbox[b];
  c = sbox[c];
  d = sbox[d];
#endif
  return word4(a, b, c, d);
}