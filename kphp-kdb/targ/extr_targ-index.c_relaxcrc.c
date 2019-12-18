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
 int /*<<< orphan*/  crc32_acc ; 
 int /*<<< orphan*/  crc32_partial (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ wptr ; 
 scalar_t__ wptr_crc ; 

__attribute__((used)) static inline void relaxcrc (void) {
  crc32_acc = crc32_partial (wptr_crc, wptr - wptr_crc, crc32_acc);
  wptr_crc = wptr;
}