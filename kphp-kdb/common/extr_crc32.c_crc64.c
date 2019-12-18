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
 long long crc64_partial (void const*,int,long long) ; 

unsigned long long crc64 (const void *data, int len) {
  return crc64_partial (data, len, -1LL) ^ -1LL;
}