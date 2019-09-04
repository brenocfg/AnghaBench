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

/* Variables and functions */
 unsigned int* crc32c_table ; 

__attribute__((used)) static unsigned crc32c_partial_old (const void *data, int len, unsigned crc) {
  const char *p = data;
  for (; len > 0; len--) {
    crc = crc32c_table[(crc ^ *p++) & 0xff] ^ (crc >> 8);
  }
  return crc;    
}