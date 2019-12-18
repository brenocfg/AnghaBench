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
typedef  int /*<<< orphan*/  uint8_t ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ar5212SetCoverageClass (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

void
ar5416SetCoverageClass(struct ath_hal *ah, uint8_t coverageclass, int now)
{

	ar5212SetCoverageClass(ah, coverageclass, now);
}