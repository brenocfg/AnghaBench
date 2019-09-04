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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  crc32_partial (size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idx_crc32_complement ; 
 size_t rptr ; 
 size_t wptr ; 

void readadv (size_t len) {
  assert (len >= 0 && len <= wptr - rptr);
  idx_crc32_complement = crc32_partial (rptr, len, idx_crc32_complement);
  rptr += len;
}