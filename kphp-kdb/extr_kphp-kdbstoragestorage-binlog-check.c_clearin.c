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
 scalar_t__ IO_BUFFSIZE ; 
 scalar_t__ bytes_read ; 
 int idx_crc32_complement ; 
 scalar_t__ io_buff ; 
 scalar_t__ rptr ; 
 scalar_t__ wptr ; 

__attribute__((used)) static void clearin (void) {
  rptr = wptr = io_buff + IO_BUFFSIZE;
  bytes_read = 0;
  idx_crc32_complement = -1;
}