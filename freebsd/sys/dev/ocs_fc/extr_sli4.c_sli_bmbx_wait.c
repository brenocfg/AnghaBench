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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  sli4_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_BMBX_DELAY_US ; 
 int SLI4_BMBX_RDY ; 
 int /*<<< orphan*/  SLI4_REG_BMBX ; 
 int /*<<< orphan*/  ocs_udelay (int /*<<< orphan*/ ) ; 
 int sli_reg_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
sli_bmbx_wait(sli4_t *sli4, uint32_t msec)
{
	uint32_t	val = 0;

	do {
		ocs_udelay(SLI4_BMBX_DELAY_US);
		val = sli_reg_read(sli4, SLI4_REG_BMBX);
		msec--;
	} while(msec && !(val & SLI4_BMBX_RDY));

	return(!(val & SLI4_BMBX_RDY));
}