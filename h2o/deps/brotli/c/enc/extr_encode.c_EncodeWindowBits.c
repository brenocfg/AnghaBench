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

/* Variables and functions */

__attribute__((used)) static void EncodeWindowBits(int lgwin, uint8_t* last_byte,
    uint8_t* last_byte_bits) {
  if (lgwin == 16) {
    *last_byte = 0;
    *last_byte_bits = 1;
  } else if (lgwin == 17) {
    *last_byte = 1;
    *last_byte_bits = 7;
  } else if (lgwin > 17) {
    *last_byte = (uint8_t)(((lgwin - 17) << 1) | 1);
    *last_byte_bits = 4;
  } else {
    *last_byte = (uint8_t)(((lgwin - 8) << 4) | 1);
    *last_byte_bits = 7;
  }
}