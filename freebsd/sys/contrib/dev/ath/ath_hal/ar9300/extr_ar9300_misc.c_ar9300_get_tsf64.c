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
typedef  int u_int64_t ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_TSF_L32 ; 
 int /*<<< orphan*/  AR_TSF_U32 ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 

u_int64_t
ar9300_get_tsf64(struct ath_hal *ah)
{
    u_int64_t tsf;

    /* XXX sync multi-word read? */
    tsf = OS_REG_READ(ah, AR_TSF_U32);
    tsf = (tsf << 32) | OS_REG_READ(ah, AR_TSF_L32);
    return tsf;
}