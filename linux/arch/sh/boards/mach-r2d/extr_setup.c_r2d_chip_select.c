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
struct sh_spi_info {int dummy; } ;

/* Variables and functions */
 int BITBANG_CS_ACTIVE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PA_RTCCE ; 
 int /*<<< orphan*/  __raw_writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r2d_chip_select(struct sh_spi_info *spi, int cs, int state)
{
	BUG_ON(cs != 0);  /* Single Epson RTC-9701JE attached on CS0 */
	__raw_writew(state == BITBANG_CS_ACTIVE, PA_RTCCE);
}