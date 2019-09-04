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
typedef  int uint32_t ;

/* Variables and functions */
 int UTF8_VALID ; 
 int* utf8d ; 

__attribute__((used)) static uint32_t
utf8_decode (uint32_t * state, uint32_t * p, uint32_t b)
{
  uint32_t type = utf8d[(uint8_t) b];

  *p = (*state != UTF8_VALID) ? (b & 0x3fu) | (*p << 6) : (0xff >> type) & (b);
  *state = utf8d[256 + *state * 16 + type];

  return *state;
}