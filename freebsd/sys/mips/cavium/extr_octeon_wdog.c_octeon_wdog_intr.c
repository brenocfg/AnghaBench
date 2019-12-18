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
struct octeon_wdog_core_softc {scalar_t__ csc_core; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_PP_POKEX (scalar_t__) ; 
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ cvmx_get_core_num () ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
octeon_wdog_intr(void *arg)
{
	struct octeon_wdog_core_softc *csc = arg;

	KASSERT(csc->csc_core == cvmx_get_core_num(),
	    ("got watchdog interrupt for core %u on core %u.",
	     csc->csc_core, cvmx_get_core_num()));

	(void)csc;

	/* Poke it! */
	cvmx_write_csr(CVMX_CIU_PP_POKEX(cvmx_get_core_num()), 1);

	return (FILTER_HANDLED);
}