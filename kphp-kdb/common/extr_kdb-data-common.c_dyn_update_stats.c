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
 int* FreeCnt ; 
 int MAX_RECORD_WORDS ; 
 int freed_blocks ; 
 int freed_bytes ; 

void dyn_update_stats (void) {
  int i;
  freed_blocks = freed_bytes = 0;
  for (i = 1; i < MAX_RECORD_WORDS; i++) {
    freed_blocks += FreeCnt[i];
    freed_bytes += i*FreeCnt[i];
  }
  freed_bytes <<= 2;
}