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
struct TYPE_2__ {int /*<<< orphan*/  blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_NAND_INVALID_PARAM ; 
 int /*<<< orphan*/  CVMX_NAND_LOG_CALLED () ; 
 int /*<<< orphan*/  CVMX_NAND_LOG_PARAM (char*,int) ; 
 int /*<<< orphan*/  CVMX_NAND_RETURN (int /*<<< orphan*/ ) ; 
 TYPE_1__* cvmx_nand_state ; 

int cvmx_nand_get_blocks(int chip)
{
    CVMX_NAND_LOG_CALLED();
    CVMX_NAND_LOG_PARAM("%d", chip);

    if ((chip < 0) || (chip > 7))
        CVMX_NAND_RETURN(CVMX_NAND_INVALID_PARAM);

    CVMX_NAND_RETURN(cvmx_nand_state[chip].blocks);
}