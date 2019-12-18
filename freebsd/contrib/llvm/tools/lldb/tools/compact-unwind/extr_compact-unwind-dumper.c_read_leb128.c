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
typedef  int uint64_t ;

/* Variables and functions */

uint64_t read_leb128(uint8_t **offset) {
  uint64_t result = 0;
  int shift = 0;
  while (1) {
    uint8_t byte = **offset;
    *offset = *offset + 1;
    result |= (byte & 0x7f) << shift;
    if ((byte & 0x80) == 0)
      break;
    shift += 7;
  }

  return result;
}