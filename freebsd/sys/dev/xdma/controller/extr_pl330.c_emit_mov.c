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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int DMAMOV ; 

__attribute__((used)) static uint32_t
emit_mov(uint8_t *buf, uint32_t reg, uint32_t val)
{

	buf[0] = DMAMOV;
	buf[1] = reg;
	buf[2] = val;
	buf[3] = val >> 8;
	buf[4] = val >> 16;
	buf[5] = val >> 24;

	return (6);
}