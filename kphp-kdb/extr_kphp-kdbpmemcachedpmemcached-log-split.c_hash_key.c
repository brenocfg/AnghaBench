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
 int compute_crc32 (char const* const,int) ; 

unsigned hash_key (const char *const key, int key_len) {
  unsigned hash = (compute_crc32 (key, key_len) >> 8) & 0x7fffff;
  return hash ? hash : 1;
}