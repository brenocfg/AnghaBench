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
 int /*<<< orphan*/  LDS (int,unsigned long) ; 

void
alpha_write_fp_reg_s (unsigned long reg, unsigned long val)
{
	switch (reg) {
	      case  0: LDS( 0, val); break;
	      case  1: LDS( 1, val); break;
	      case  2: LDS( 2, val); break;
	      case  3: LDS( 3, val); break;
	      case  4: LDS( 4, val); break;
	      case  5: LDS( 5, val); break;
	      case  6: LDS( 6, val); break;
	      case  7: LDS( 7, val); break;
	      case  8: LDS( 8, val); break;
	      case  9: LDS( 9, val); break;
	      case 10: LDS(10, val); break;
	      case 11: LDS(11, val); break;
	      case 12: LDS(12, val); break;
	      case 13: LDS(13, val); break;
	      case 14: LDS(14, val); break;
	      case 15: LDS(15, val); break;
	      case 16: LDS(16, val); break;
	      case 17: LDS(17, val); break;
	      case 18: LDS(18, val); break;
	      case 19: LDS(19, val); break;
	      case 20: LDS(20, val); break;
	      case 21: LDS(21, val); break;
	      case 22: LDS(22, val); break;
	      case 23: LDS(23, val); break;
	      case 24: LDS(24, val); break;
	      case 25: LDS(25, val); break;
	      case 26: LDS(26, val); break;
	      case 27: LDS(27, val); break;
	      case 28: LDS(28, val); break;
	      case 29: LDS(29, val); break;
	      case 30: LDS(30, val); break;
	      case 31: LDS(31, val); break;
	}
}