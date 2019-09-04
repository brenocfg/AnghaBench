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
 int crc32_partial (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  idx_loaded_bytes ; 
 scalar_t__ idx_ptr_crc ; 
 scalar_t__ idx_rptr ; 
 int read_crc32_acc ; 

__attribute__((used)) static inline unsigned idx_relax_crc32 (void) {
  if (idx_ptr_crc < idx_rptr) {
    idx_loaded_bytes += idx_rptr - idx_ptr_crc;
    read_crc32_acc = crc32_partial (idx_ptr_crc, idx_rptr - idx_ptr_crc, read_crc32_acc);
    idx_ptr_crc = idx_rptr;
  }
  return ~read_crc32_acc;
}