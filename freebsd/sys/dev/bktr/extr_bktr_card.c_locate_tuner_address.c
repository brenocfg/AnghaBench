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
typedef  int /*<<< orphan*/  bktr_ptr_t ;

/* Variables and functions */
 scalar_t__ ABSENT ; 
 scalar_t__ i2cRead (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int locate_tuner_address( bktr_ptr_t bktr) {
  if (i2cRead( bktr, 0xc1) != ABSENT) return 0xc0;
  if (i2cRead( bktr, 0xc3) != ABSENT) return 0xc2;
  if (i2cRead( bktr, 0xc5) != ABSENT) return 0xc4;
  if (i2cRead( bktr, 0xc7) != ABSENT) return 0xc6;
  return -1; /* no tuner found */
}