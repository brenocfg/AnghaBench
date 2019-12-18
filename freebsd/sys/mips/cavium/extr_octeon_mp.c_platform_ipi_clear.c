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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_MBOX_CLRX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuid ; 
 int cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 

void
platform_ipi_clear(void)
{
	uint64_t action;

	action = cvmx_read_csr(CVMX_CIU_MBOX_CLRX(PCPU_GET(cpuid)));
	KASSERT(action == 1, ("unexpected IPIs: %#jx", (uintmax_t)action));
	cvmx_write_csr(CVMX_CIU_MBOX_CLRX(PCPU_GET(cpuid)), action);
}