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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline void write32_be(uint32_t v, uint8_t buf[4])
{
  *buf++ = (v >> 24) & 0xff;
  *buf++ = (v >> 16) & 0xff;
  *buf++ = (v >> 8) & 0xff;
  *buf   = v & 0xff;
}