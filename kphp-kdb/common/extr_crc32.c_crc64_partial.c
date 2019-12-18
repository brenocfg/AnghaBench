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
 unsigned long long* crc64_table ; 

unsigned long long crc64_partial (const void *data, int len, unsigned long long crc) {
  const char *p = data;
  for (; len > 0; len--) {
    crc = crc64_table[(crc ^ *p++) & 0xff] ^ (crc >> 8);
  }
  return crc;    
}