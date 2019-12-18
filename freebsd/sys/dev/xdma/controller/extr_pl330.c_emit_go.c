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
 int DMAGO ; 

__attribute__((used)) static uint32_t
emit_go(uint8_t *buf, uint32_t chan_id,
    uint32_t addr, uint8_t non_secure)
{

	buf[0] = DMAGO;
	buf[0] |= (non_secure << 1);

	buf[1] = chan_id;
	buf[2] = addr;
	buf[3] = addr >> 8;
	buf[4] = addr >> 16;
	buf[5] = addr >> 24;

	return (6);
}