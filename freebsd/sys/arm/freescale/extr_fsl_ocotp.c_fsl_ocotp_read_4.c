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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int bus_size_t ;

/* Variables and functions */
 int FSL_OCOTP_LAST_REG ; 
 int /*<<< orphan*/  RD4 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fsl_ocotp_devmap () ; 
 int /*<<< orphan*/ * ocotp_regs ; 
 int /*<<< orphan*/ * ocotp_sc ; 
 int /*<<< orphan*/  panic (char*) ; 

uint32_t
fsl_ocotp_read_4(bus_size_t off)
{

	if (off > FSL_OCOTP_LAST_REG)
		panic("fsl_ocotp_read_4: offset out of range");

	/* If we have a softcontext use the regular bus_space read. */
	if (ocotp_sc != NULL)
		return (RD4(ocotp_sc, off));

	/*
	 * Otherwise establish a tempory device mapping if necessary, and read
	 * the device without any help from bus_space.
	 *
	 * XXX Eventually the code from there down can be deleted.
	 */
	if (ocotp_regs == NULL)
		fsl_ocotp_devmap();

	return (ocotp_regs[off / 4]);
}