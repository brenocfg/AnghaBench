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
typedef  int /*<<< orphan*/  u_int ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_TIME_OUT ; 
 int /*<<< orphan*/  AR_TIME_OUT_CTS ; 
 int /*<<< orphan*/  MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_hal_mac_usec (struct ath_hal*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
ar9300_freebsd_get_cts_timeout(struct ath_hal *ah)
{
    u_int clks = MS(OS_REG_READ(ah, AR_TIME_OUT), AR_TIME_OUT_CTS);
    return ath_hal_mac_usec(ah, clks);      /* convert from system clocks */
}