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
typedef  unsigned char uint32_t ;
typedef  int int8_t ;

/* Variables and functions */

uint32_t dl_sscanf_uint32(const char *buf) {
  uint32_t ret = 0;
  const char *tail = buf;
  int8_t i;
  for (i = 0; i < 4; i++) {
    ret |= ((((unsigned char) *tail++) & 0xFF) << (i<<3));
  }
  return ret;
}