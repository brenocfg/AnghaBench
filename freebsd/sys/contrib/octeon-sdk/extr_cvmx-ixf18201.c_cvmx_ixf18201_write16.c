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
 int /*<<< orphan*/  IXF_TRANS_TYPE ; 
 int /*<<< orphan*/  IXF_WR_DATA_16 ; 
 int /*<<< orphan*/  cvmx_wait (int) ; 
 int /*<<< orphan*/  cvmx_write64_uint16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write64_uint8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cvmx_ixf18201_write16(uint16_t reg_addr, uint16_t data)
{
    cvmx_write64_uint16(IXF_ADDR_16, reg_addr);
    cvmx_write64_uint16(IXF_WR_DATA_16, data);
    cvmx_write64_uint8(IXF_TRANS_TYPE, 0);
    cvmx_wait(800000);
}