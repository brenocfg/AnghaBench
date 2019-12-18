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
typedef  int uint32_t ;
typedef  int int8_t ;

/* Variables and functions */

char *dl_sprintf_uint32(char *buf, uint32_t value) {
  char *tail = buf;
  int8_t i;
  for (i = 0; i < 4; i++) {
    *tail++ = (unsigned char)((value >> (i<<3)) & 0xFF);
  }
  return tail;
}