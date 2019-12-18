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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  IXF_ADDR_16 ; 
 int /*<<< orphan*/  IXF_RD_DATA_16 ; 
 int /*<<< orphan*/  IXF_TRANS_TYPE ; 
 int /*<<< orphan*/  cvmx_read64_uint16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_wait (int) ; 
 int /*<<< orphan*/  cvmx_write64_uint16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write64_uint8 (int /*<<< orphan*/ ,int) ; 

uint16_t cvmx_ixf18201_read16(uint16_t reg_addr)
{
    cvmx_write64_uint16(IXF_ADDR_16, reg_addr);
    cvmx_write64_uint8(IXF_TRANS_TYPE, 1);  // Do read
    cvmx_wait(800000);

    /* Read result */
    return(cvmx_read64_uint16(IXF_RD_DATA_16));
}