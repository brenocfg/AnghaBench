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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ath_hal {int dummy; } ;
typedef  scalar_t__ HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AR_RX_FILTER ; 
 int /*<<< orphan*/  AR_RX_PROM ; 
 int /*<<< orphan*/  OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ar9300_promisc_mode(struct ath_hal *ah, HAL_BOOL enable)
{
    u_int32_t reg_val = 0;
    reg_val =  OS_REG_READ(ah, AR_RX_FILTER);
    if (enable){
        reg_val |= AR_RX_PROM;
    } else{ /*Disable promisc mode */
        reg_val &= ~AR_RX_PROM;
    }    
    OS_REG_WRITE(ah, AR_RX_FILTER, reg_val);
}