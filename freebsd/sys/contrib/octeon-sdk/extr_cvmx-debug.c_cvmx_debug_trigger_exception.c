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

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_DINT ; 
 int /*<<< orphan*/  CVMX_MIO_BOOT_BIST_STAT ; 
 unsigned int cvmx_get_core_num () ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,unsigned int) ; 

void cvmx_debug_trigger_exception(void)
{
  /* Set CVMX_CIU_DINT to enter debug exception handler.  */
  cvmx_write_csr (CVMX_CIU_DINT, 1u << cvmx_get_core_num ());
  /* Perform an immediate read after every write to an RSL register to force
     the write to complete. It doesn't matter what RSL read we do, so we
     choose CVMX_MIO_BOOT_BIST_STAT because it is fast and harmless */
  cvmx_read_csr (CVMX_MIO_BOOT_BIST_STAT);
}