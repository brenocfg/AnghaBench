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
struct ath_hal {int dummy; } ;
typedef  int HAL_BOOL ;

/* Variables and functions */
 scalar_t__ IS_2417 (struct ath_hal*) ; 
 scalar_t__ IS_2425 (struct ath_hal*) ; 

__attribute__((used)) static HAL_BOOL
ar2425Probe(struct ath_hal *ah)
{
	return IS_2425(ah) || IS_2417(ah);
}