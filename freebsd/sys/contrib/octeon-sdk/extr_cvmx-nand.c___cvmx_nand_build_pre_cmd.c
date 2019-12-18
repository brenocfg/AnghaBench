#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ cvmx_nand_status_t ;
struct TYPE_16__ {int cmd_data; int four; int /*<<< orphan*/  clen3; int /*<<< orphan*/  clen2; int /*<<< orphan*/  clen1; } ;
struct TYPE_17__ {int adr_byte_num; int adr_bytes_l; int adr_bytes_h; int five; int /*<<< orphan*/  alen4; int /*<<< orphan*/  alen3; int /*<<< orphan*/  alen2; int /*<<< orphan*/  alen1; } ;
struct TYPE_15__ {int two; int n; } ;
struct TYPE_14__ {int chip; int one; int three; int width; } ;
struct TYPE_13__ {int fifteen; int one; } ;
struct TYPE_12__ {int one; int /*<<< orphan*/  tim_par7; int /*<<< orphan*/  tim_par6; int /*<<< orphan*/  tim_par5; int /*<<< orphan*/  tim_par4; int /*<<< orphan*/  tim_par3; int /*<<< orphan*/  tim_par2; int /*<<< orphan*/  tim_par1; int /*<<< orphan*/  tim_mult; } ;
struct TYPE_18__ {TYPE_5__ cle; TYPE_6__ ale; TYPE_4__ wait; TYPE_3__ chip_en; TYPE_2__ bus_acq; TYPE_1__ set_tm_par; } ;
typedef  TYPE_7__ cvmx_nand_cmd_t ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_11__ {int flags; int page_size; int /*<<< orphan*/ * clen; int /*<<< orphan*/ * alen; int /*<<< orphan*/ * tim_par; int /*<<< orphan*/  tim_mult; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_NAND_LOG_CALLED () ; 
 scalar_t__ CVMX_NAND_NO_MEMORY ; 
 int /*<<< orphan*/  CVMX_NAND_RETURN (scalar_t__) ; 
 int CVMX_NAND_STATE_16BIT ; 
 scalar_t__ CVMX_NAND_SUCCESS ; 
 int __cvmx_nand_get_address_cycles (int) ; 
 int __cvmx_nand_get_column_bits (int) ; 
 TYPE_10__* cvmx_nand_state ; 
 scalar_t__ cvmx_nand_submit (TYPE_7__) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline cvmx_nand_status_t __cvmx_nand_build_pre_cmd(int chip, int cmd_data, int num_address_cycles, uint64_t nand_address, int cmd_data2)
{
    cvmx_nand_status_t result;
    cvmx_nand_cmd_t cmd;

    CVMX_NAND_LOG_CALLED();

    /* Send timing parameters */
    memset(&cmd,  0,  sizeof(cmd));
    cmd.set_tm_par.one = 1;
    cmd.set_tm_par.tim_mult = cvmx_nand_state[chip].tim_mult;
    /* tim_par[0] unused */
    cmd.set_tm_par.tim_par1 = cvmx_nand_state[chip].tim_par[1];
    cmd.set_tm_par.tim_par2 = cvmx_nand_state[chip].tim_par[2];
    cmd.set_tm_par.tim_par3 = cvmx_nand_state[chip].tim_par[3];
    cmd.set_tm_par.tim_par4 = cvmx_nand_state[chip].tim_par[4];
    cmd.set_tm_par.tim_par5 = cvmx_nand_state[chip].tim_par[5];
    cmd.set_tm_par.tim_par6 = cvmx_nand_state[chip].tim_par[6];
    cmd.set_tm_par.tim_par7 = cvmx_nand_state[chip].tim_par[7];
    result = cvmx_nand_submit(cmd);
    if (result)
        CVMX_NAND_RETURN(result);

    /* Send bus select */
    memset(&cmd,  0,  sizeof(cmd));
    cmd.bus_acq.fifteen = 15;
    cmd.bus_acq.one = 1;
    result = cvmx_nand_submit(cmd);
    if (result)
        CVMX_NAND_RETURN(result);

    /* Send chip select */
    memset(&cmd,  0,  sizeof(cmd));
    cmd.chip_en.chip = chip;
    cmd.chip_en.one = 1;
    cmd.chip_en.three = 3;
    cmd.chip_en.width = (cvmx_nand_state[chip].flags & CVMX_NAND_STATE_16BIT) ? 2 : 1;
    result = cvmx_nand_submit(cmd);
    if (result)
        CVMX_NAND_RETURN(result);

    /* Send wait, fixed time
    ** This meets chip enable to command latch enable timing.
    ** This is tCS - tCLS from the ONFI spec.
    ** Use tWP as a proxy, as this is adequate for
    ** all ONFI 1.0 timing modes. */
    memset(&cmd,  0,  sizeof(cmd));
    cmd.wait.two = 2;
    cmd.wait.n = 1;
    if (cvmx_nand_submit(cmd))
        CVMX_NAND_RETURN(CVMX_NAND_NO_MEMORY);

    /* Send CLE */
    memset(&cmd,  0,  sizeof(cmd));
    cmd.cle.cmd_data = cmd_data;
    cmd.cle.clen1 = cvmx_nand_state[chip].clen[0];
    cmd.cle.clen2 = cvmx_nand_state[chip].clen[1];
    cmd.cle.clen3 = cvmx_nand_state[chip].clen[2];
    cmd.cle.four = 4;
    result = cvmx_nand_submit(cmd);
    if (result)
        CVMX_NAND_RETURN(result);

    /* Send ALE */
    if (num_address_cycles)
    {
        memset(&cmd,  0,  sizeof(cmd));
        cmd.ale.adr_byte_num = num_address_cycles;
        if (num_address_cycles < __cvmx_nand_get_address_cycles(chip))
        {
            cmd.ale.adr_bytes_l = nand_address;
            cmd.ale.adr_bytes_h = nand_address >> 32;
        }
        else
        {
            int column_bits = __cvmx_nand_get_column_bits(chip);
            int column_shift = ((column_bits + 7) >> 3) << 3;
            int column = nand_address & (cvmx_nand_state[chip].page_size-1);
            int row = nand_address >> column_bits;
            cmd.ale.adr_bytes_l = column + (row << column_shift);
            cmd.ale.adr_bytes_h = row >> (32 - column_shift);
        }
        cmd.ale.alen1 = cvmx_nand_state[chip].alen[0];
        cmd.ale.alen2 = cvmx_nand_state[chip].alen[1];
        cmd.ale.alen3 = cvmx_nand_state[chip].alen[2];
        cmd.ale.alen4 = cvmx_nand_state[chip].alen[3];
        cmd.ale.five = 5;
        result = cvmx_nand_submit(cmd);
        if (result)
            CVMX_NAND_RETURN(result);
    }

    /* Send CLE 2 */
    if (cmd_data2)
    {
        memset(&cmd,  0,  sizeof(cmd));
        cmd.cle.cmd_data = cmd_data2;
        cmd.cle.clen1 = cvmx_nand_state[chip].clen[0];
        cmd.cle.clen2 = cvmx_nand_state[chip].clen[1];
        cmd.cle.clen3 = cvmx_nand_state[chip].clen[2];
        cmd.cle.four = 4;
        result = cvmx_nand_submit(cmd);
        if (result)
            CVMX_NAND_RETURN(result);
    }

    CVMX_NAND_RETURN(CVMX_NAND_SUCCESS);
}