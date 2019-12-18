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
struct TYPE_2__ {scalar_t__ fr_byt; } ;
union cvmx_ndf_misc {TYPE_1__ s; int /*<<< orphan*/  u64; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_NAND_LOG_CALLED () ; 
 int /*<<< orphan*/  CVMX_NAND_RETURN (int) ; 
 int /*<<< orphan*/  CVMX_NDF_MISC ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int __cvmx_nand_get_free_cmd_bytes(void)
{
    union cvmx_ndf_misc ndf_misc;
    CVMX_NAND_LOG_CALLED();
    ndf_misc.u64 = cvmx_read_csr(CVMX_NDF_MISC);
    CVMX_NAND_RETURN((int)ndf_misc.s.fr_byt);
}