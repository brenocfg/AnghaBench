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
 scalar_t__ AR_SREV_HOWL (struct ath_hal*) ; 
 scalar_t__ AR_SREV_OWL (struct ath_hal*) ; 
 scalar_t__ AR_SREV_SOWL (struct ath_hal*) ; 

__attribute__((used)) static HAL_BOOL
ar2133Probe(struct ath_hal *ah)
{
	return (AR_SREV_OWL(ah) || AR_SREV_HOWL(ah) || AR_SREV_SOWL(ah));
}