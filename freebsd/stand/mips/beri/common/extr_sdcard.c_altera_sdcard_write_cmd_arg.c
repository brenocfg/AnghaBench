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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALTERA_SDCARD_OFF_CMD_ARG ; 
 int /*<<< orphan*/  altera_sdcard_write_uint32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
altera_sdcard_write_cmd_arg(uint32_t cmd_arg)
{

	altera_sdcard_write_uint32(ALTERA_SDCARD_OFF_CMD_ARG, cmd_arg);
}