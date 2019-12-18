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
typedef  int uint32_t ;
struct mmc_softc {int dummy; } ;

/* Variables and functions */
 int MMC_OCR_VOLTAGE ; 

__attribute__((used)) static uint32_t
mmc_select_vdd(struct mmc_softc *sc, uint32_t ocr)
{

	return (ocr & MMC_OCR_VOLTAGE);
}