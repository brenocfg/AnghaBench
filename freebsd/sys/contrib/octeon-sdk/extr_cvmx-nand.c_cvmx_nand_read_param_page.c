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
typedef  int uint64_t ;
typedef  int ULL ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CVMX_NAND_INVALID_PARAM ; 
 int /*<<< orphan*/  CVMX_NAND_LOG_CALLED () ; 
 int /*<<< orphan*/  CVMX_NAND_LOG_PARAM (char*,int) ; 
 int /*<<< orphan*/  CVMX_NAND_RETURN (int) ; 
 int CVMX_NAND_STATE_16BIT ; 
 int /*<<< orphan*/  NAND_COMMAND_READ_PARAM_PAGE ; 
 int /*<<< orphan*/  __cvmx_nand_fixup_16bit_id_reads (int /*<<< orphan*/ ,int) ; 
 int __cvmx_nand_low_level_read (int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* cvmx_nand_state ; 
 int /*<<< orphan*/  cvmx_phys_to_ptr (int) ; 

int cvmx_nand_read_param_page(int chip, uint64_t buffer_address, int buffer_length)
{
    int bytes;

    CVMX_NAND_LOG_CALLED();
    CVMX_NAND_LOG_PARAM("%d", chip);
    CVMX_NAND_LOG_PARAM("0x%llx", (ULL)buffer_address);
    CVMX_NAND_LOG_PARAM("%d", buffer_length);

    if ((chip < 0) || (chip > 7))
        CVMX_NAND_RETURN(CVMX_NAND_INVALID_PARAM);
    if (!buffer_address)
        CVMX_NAND_RETURN(CVMX_NAND_INVALID_PARAM);
    if (buffer_address & 7)
        CVMX_NAND_RETURN(CVMX_NAND_INVALID_PARAM);
    if (buffer_length & 7)
        CVMX_NAND_RETURN(CVMX_NAND_INVALID_PARAM);
    if (!buffer_length)
        CVMX_NAND_RETURN(CVMX_NAND_INVALID_PARAM);

    bytes = __cvmx_nand_low_level_read(chip, NAND_COMMAND_READ_PARAM_PAGE, 1, 0x0, 0, buffer_address, buffer_length);
    if (cvmx_nand_state[chip].flags & CVMX_NAND_STATE_16BIT)
        __cvmx_nand_fixup_16bit_id_reads(cvmx_phys_to_ptr(buffer_address), buffer_length);
    CVMX_NAND_RETURN(bytes);
}