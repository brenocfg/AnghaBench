#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pos0_val; int pos0; int pos1_val; int pos1; int pos2_val; int pos2; int pos3_val; int pos3; int pos4_val; int pos4; int pos5_val; int pos5; int pos6_val; int pos6; int pos7_val; int pos7; } ;
struct TYPE_4__ {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_pip_bsel_ext_posx_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_PIP_BSEL_EXT_POSX (int) ; 
 int /*<<< orphan*/  OCTEON_FEATURE_BIT_EXTRACTOR ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cvmx_pip_set_bsel_pos(int bit, int pos, int val)
{
    cvmx_pip_bsel_ext_posx_t bsel_pos;

    /* The bit select extractor is available in CN61XX and CN68XX pass2.0 onwards. */
    if (!octeon_has_feature(OCTEON_FEATURE_BIT_EXTRACTOR))
        return;

    if (bit < 0 || bit > 3)
    {
        cvmx_dprintf("ERROR: cvmx_pip_set_bsel_pos: Invalid Bit-Select Extractor (%d) passed\n", bit);
        return;
    }

    bsel_pos.u64 = cvmx_read_csr(CVMX_PIP_BSEL_EXT_POSX(bit));
    switch(pos)
    {
        case 0:
            bsel_pos.s.pos0_val = 1;
            bsel_pos.s.pos0 = val & 0x7f;
            break;
        case 1:
            bsel_pos.s.pos1_val = 1;
            bsel_pos.s.pos1 = val & 0x7f;
            break;
        case 2:
            bsel_pos.s.pos2_val = 1;
            bsel_pos.s.pos2 = val & 0x7f;
            break;
        case 3:
            bsel_pos.s.pos3_val = 1;
            bsel_pos.s.pos3 = val & 0x7f;
            break;
        case 4:
            bsel_pos.s.pos4_val = 1;
            bsel_pos.s.pos4 = val & 0x7f;
            break;
        case 5:
            bsel_pos.s.pos5_val = 1;
            bsel_pos.s.pos5 = val & 0x7f;
            break;
        case 6:
            bsel_pos.s.pos6_val = 1;
            bsel_pos.s.pos6 = val & 0x7f;
            break;
        case 7:
            bsel_pos.s.pos7_val = 1;
            bsel_pos.s.pos7 = val & 0x7f;
            break;
        default:
            cvmx_dprintf("Warning: cvmx_pip_set_bsel_pos: Invalid pos(%d)\n", pos);
            break;
    }
    cvmx_write_csr(CVMX_PIP_BSEL_EXT_POSX(bit), bsel_pos.u64);
}