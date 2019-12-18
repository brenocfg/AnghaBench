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
typedef  int u_int8_t ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  HALASSERT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HAL_BOOL
ar9300_invalid_stbc_cfg(int tx_chains, u_int8_t rate_code)
{
    switch (tx_chains) {
    case 0: /* Single Chain */
        return AH_TRUE;

    case 1: /* 2 Chains */
        if ((rate_code < 0x80) || (rate_code > 0x87)) {
            return AH_TRUE;
        } else {
            return AH_FALSE;
        }

    case 2: /* 3 Chains */
        if ((rate_code < 0x80) || (rate_code > 0x87)) {
            return AH_TRUE;
        } else {
            return AH_FALSE;
        }

    default:
        HALASSERT(0);
        break;
    } 

    return AH_TRUE;
}