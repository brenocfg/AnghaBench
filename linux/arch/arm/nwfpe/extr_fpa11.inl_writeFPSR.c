#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int fpsr; } ;
typedef  int FPSR ;
typedef  TYPE_1__ FPA11 ;

/* Variables and functions */
 TYPE_1__* GET_FPA11 () ; 
 int MASK_SYSID ; 

__attribute__((used)) static inline void writeFPSR(FPSR reg)
{
	FPA11 *fpa11 = GET_FPA11();
	/* the sysid byte in the status register is readonly */
	fpa11->fpsr = (fpa11->fpsr & MASK_SYSID) | (reg & ~MASK_SYSID);
}