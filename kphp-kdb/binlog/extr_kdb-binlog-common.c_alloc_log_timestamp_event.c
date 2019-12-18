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
 int /*<<< orphan*/  LEV_TIMESTAMP ; 
 int /*<<< orphan*/  alloc_log_crc32_event () ; 
 int /*<<< orphan*/  alloc_log_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bytes_after_crc32 ; 
 int disable_crc32 ; 
 int disable_ts ; 
 scalar_t__ log_crc32_interval2 ; 

__attribute__((used)) static inline void alloc_log_timestamp_event (void) {
  if (bytes_after_crc32 >= log_crc32_interval2 && !(disable_crc32 & 1)) {
    alloc_log_crc32_event ();
  } else if (!(disable_ts & 1)) {
    alloc_log_event (LEV_TIMESTAMP, 0, 0);
  }
}