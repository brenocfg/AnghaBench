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
 int /*<<< orphan*/  STT (int,unsigned long) ; 

unsigned long
alpha_read_fp_reg (unsigned long reg)
{
	unsigned long val;

	switch (reg) {
	      case  0: STT( 0, val); break;
	      case  1: STT( 1, val); break;
	      case  2: STT( 2, val); break;
	      case  3: STT( 3, val); break;
	      case  4: STT( 4, val); break;
	      case  5: STT( 5, val); break;
	      case  6: STT( 6, val); break;
	      case  7: STT( 7, val); break;
	      case  8: STT( 8, val); break;
	      case  9: STT( 9, val); break;
	      case 10: STT(10, val); break;
	      case 11: STT(11, val); break;
	      case 12: STT(12, val); break;
	      case 13: STT(13, val); break;
	      case 14: STT(14, val); break;
	      case 15: STT(15, val); break;
	      case 16: STT(16, val); break;
	      case 17: STT(17, val); break;
	      case 18: STT(18, val); break;
	      case 19: STT(19, val); break;
	      case 20: STT(20, val); break;
	      case 21: STT(21, val); break;
	      case 22: STT(22, val); break;
	      case 23: STT(23, val); break;
	      case 24: STT(24, val); break;
	      case 25: STT(25, val); break;
	      case 26: STT(26, val); break;
	      case 27: STT(27, val); break;
	      case 28: STT(28, val); break;
	      case 29: STT(29, val); break;
	      case 30: STT(30, val); break;
	      case 31: STT(31, val); break;
	      default: return 0;
	}
	return val;
}