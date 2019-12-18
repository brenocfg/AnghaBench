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
struct au1550_spi_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCSR_RESETS ; 
 int /*<<< orphan*/  BCSR_RESETS_SPISEL ; 
 int /*<<< orphan*/  bcsr_mod (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void db1200_spi_cs_en(struct au1550_spi_info *spi, int cs, int pol)
{
	if (cs)
		bcsr_mod(BCSR_RESETS, 0, BCSR_RESETS_SPISEL);
	else
		bcsr_mod(BCSR_RESETS, BCSR_RESETS_SPISEL, 0);
}