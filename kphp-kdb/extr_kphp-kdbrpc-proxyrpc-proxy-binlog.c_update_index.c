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
 int RPC_PROXY_INDEX_MAGIC ; 
 int* cur ; 

void update_index (long long pos, unsigned crc32, int timestamp) {
  cur[0] = RPC_PROXY_INDEX_MAGIC;
  *(long long *)(cur + 1) = pos;
  cur[3] = crc32;
  cur[4] = timestamp;
}