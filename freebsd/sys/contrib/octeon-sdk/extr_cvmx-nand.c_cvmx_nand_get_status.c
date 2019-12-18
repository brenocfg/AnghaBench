#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CVMX_NAND_INVALID_PARAM ; 
 int /*<<< orphan*/  CVMX_NAND_LOG_CALLED () ; 
 int /*<<< orphan*/  CVMX_NAND_LOG_PARAM (char*,int) ; 
 int /*<<< orphan*/  CVMX_NAND_RETURN (int) ; 
 int CVMX_NAND_STATE_16BIT ; 
 int /*<<< orphan*/  NAND_COMMAND_STATUS ; 
 int __cvmx_nand_low_level_read (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ cvmx_nand_buffer ; 
 TYPE_1__* cvmx_nand_state ; 
 int /*<<< orphan*/  cvmx_ptr_to_phys (scalar_t__) ; 

int cvmx_nand_get_status(int chip)
{
    int status;
    int offset = !!(cvmx_nand_state[chip].flags & CVMX_NAND_STATE_16BIT);  /* Normalize flag to 0/1 */

    CVMX_NAND_LOG_CALLED();
    CVMX_NAND_LOG_PARAM("%d", chip);

    if ((chip < 0) || (chip > 7))
        CVMX_NAND_RETURN(CVMX_NAND_INVALID_PARAM);

    *((uint8_t*)cvmx_nand_buffer + offset)  = 0xff;
    status = __cvmx_nand_low_level_read(chip, NAND_COMMAND_STATUS, 0, 0, 0, cvmx_ptr_to_phys(cvmx_nand_buffer), 8);
    if (status > 0)
        status = *((uint8_t*)cvmx_nand_buffer + offset);

    CVMX_NAND_RETURN(status);
}