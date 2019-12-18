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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int u_int ;

/* Variables and functions */
 int /*<<< orphan*/  AR9300_DEF_MODE ; 
 int /*<<< orphan*/  AR9300_STBC_MODE ; 
 int HAL_RATESERIES_STBC ; 

__attribute__((used)) static u_int8_t
ar9300_get_tx_mode(u_int rate_flags)
{

    /* Check whether STBC is enabled if TxBF is not enabled */
    if (rate_flags & HAL_RATESERIES_STBC){
        return AR9300_STBC_MODE;
    }
    return AR9300_DEF_MODE;
}