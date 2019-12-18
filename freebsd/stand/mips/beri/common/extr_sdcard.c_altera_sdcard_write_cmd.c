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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALTERA_SDCARD_OFF_CMD ; 
 int /*<<< orphan*/  altera_sdcard_write_uint16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
altera_sdcard_write_cmd(uint16_t cmd)
{

	altera_sdcard_write_uint16(ALTERA_SDCARD_OFF_CMD, cmd);
}