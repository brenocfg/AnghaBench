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
typedef  int /*<<< orphan*/  PACB ;

/* Variables and functions */
 int GTIMEOUT ; 
 int /*<<< orphan*/  TRMREG_GEN_STATUS ; 
 int /*<<< orphan*/  TRMREG_GEN_TIMER ; 
 int trm_reg_read8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trm_reg_write8 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
NVRAM_trm_wait_30us(PACB pACB)
{
  
	/*    ScsiPortStallExecution(30);	 wait 30 us	*/
	trm_reg_write8(5, TRMREG_GEN_TIMER);
	while (!(trm_reg_read8(TRMREG_GEN_STATUS) & GTIMEOUT));
	return;
}