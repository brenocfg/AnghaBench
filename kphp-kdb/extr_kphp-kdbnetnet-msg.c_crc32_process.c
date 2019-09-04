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
 unsigned int crc32_partial (void const*,int,unsigned int) ; 

void crc32_process (void *extra, const void *data, int len) {
  unsigned crc32 = *(unsigned *)extra;
  *(unsigned *)extra = crc32_partial (data, len, crc32);
}