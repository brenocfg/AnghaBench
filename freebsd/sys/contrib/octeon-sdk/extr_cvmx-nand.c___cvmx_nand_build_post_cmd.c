#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ cvmx_nand_status_t ;
struct TYPE_7__ {int fifteen; } ;
struct TYPE_6__ {int three; } ;
struct TYPE_8__ {TYPE_2__ bus_rel; TYPE_1__ chip_dis; } ;
typedef  TYPE_3__ cvmx_nand_cmd_t ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_NAND_LOG_CALLED () ; 
 int /*<<< orphan*/  CVMX_NAND_RETURN (scalar_t__) ; 
 scalar_t__ CVMX_NAND_SUCCESS ; 
 int /*<<< orphan*/  CVMX_NDF_DRBELL ; 
 scalar_t__ cvmx_nand_submit (TYPE_3__) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline cvmx_nand_status_t __cvmx_nand_build_post_cmd(void)
{
    cvmx_nand_status_t result;
    cvmx_nand_cmd_t cmd;

    CVMX_NAND_LOG_CALLED();

    /* Send chip deselect */
    memset(&cmd,  0,  sizeof(cmd));
    cmd.chip_dis.three = 3;
    result = cvmx_nand_submit(cmd);
    if (result)
        CVMX_NAND_RETURN(result);

    /* Send bus release */
    memset(&cmd,  0,  sizeof(cmd));
    cmd.bus_rel.fifteen = 15;
    result = cvmx_nand_submit(cmd);
    if (result)
        CVMX_NAND_RETURN(result);

    /* Ring the doorbell */
    cvmx_write_csr(CVMX_NDF_DRBELL, 1);
    CVMX_NAND_RETURN(CVMX_NAND_SUCCESS);
}