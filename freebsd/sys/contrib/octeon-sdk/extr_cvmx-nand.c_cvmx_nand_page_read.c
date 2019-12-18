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
struct TYPE_2__ {int page_size; int flags; } ;

/* Variables and functions */
 int CVMX_NAND_INVALID_PARAM ; 
 int /*<<< orphan*/  CVMX_NAND_LOG_CALLED () ; 
 int /*<<< orphan*/  CVMX_NAND_LOG_PARAM (char*,int) ; 
 int /*<<< orphan*/  CVMX_NAND_RETURN (int) ; 
 int CVMX_NAND_STATE_16BIT ; 
 int /*<<< orphan*/  NAND_COMMAND_READ ; 
 int /*<<< orphan*/  NAND_COMMAND_READ_FIN ; 
 int /*<<< orphan*/  __cvmx_nand_get_address_cycles (int) ; 
 int __cvmx_nand_low_level_read (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* cvmx_nand_state ; 

int cvmx_nand_page_read(int chip, uint64_t nand_address, uint64_t buffer_address, int buffer_length)
{
    int bytes;

    CVMX_NAND_LOG_CALLED();
    CVMX_NAND_LOG_PARAM("%d", chip);
    CVMX_NAND_LOG_PARAM("0x%llx", (ULL)nand_address);
    CVMX_NAND_LOG_PARAM("0x%llx", (ULL)buffer_address);
    CVMX_NAND_LOG_PARAM("%d", buffer_length);

    if ((chip < 0) || (chip > 7))
        CVMX_NAND_RETURN(CVMX_NAND_INVALID_PARAM);
    if (!cvmx_nand_state[chip].page_size)
        CVMX_NAND_RETURN(CVMX_NAND_INVALID_PARAM);
    if (!buffer_address)
        CVMX_NAND_RETURN(CVMX_NAND_INVALID_PARAM);
    if (buffer_address & 7)
        CVMX_NAND_RETURN(CVMX_NAND_INVALID_PARAM);
    if (buffer_length & 7)
        CVMX_NAND_RETURN(CVMX_NAND_INVALID_PARAM);
    if (!buffer_length)
        CVMX_NAND_RETURN(CVMX_NAND_INVALID_PARAM);

    /* For 16 bit mode, addresses within a page are word address, rather than byte addresses */
    if (cvmx_nand_state[chip].flags & CVMX_NAND_STATE_16BIT)
            nand_address = (nand_address & ~(cvmx_nand_state[chip].page_size - 1)) |  ((nand_address & (cvmx_nand_state[chip].page_size - 1)) >> 1);

    bytes = __cvmx_nand_low_level_read(chip, NAND_COMMAND_READ, __cvmx_nand_get_address_cycles(chip), nand_address, NAND_COMMAND_READ_FIN, buffer_address, buffer_length);
    CVMX_NAND_RETURN(bytes);
}