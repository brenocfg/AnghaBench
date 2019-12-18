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
 int /*<<< orphan*/  ALTERA_SDCARD_OFF_ASR ; 
 int /*<<< orphan*/  altera_sdcard_read_uint16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline uint16_t
altera_sdcard_read_asr(void)
{

	return (altera_sdcard_read_uint16(ALTERA_SDCARD_OFF_ASR));
}