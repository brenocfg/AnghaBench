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
 int DMALP ; 

__attribute__((used)) static uint32_t
emit_lp(uint8_t *buf, uint8_t idx, uint32_t iter)
{

	if (idx > 1)
		return (0); /* We have two loops only. */

	buf[0] = DMALP;
	buf[0] |= (idx << 1);
	buf[1] = (iter - 1) & 0xff;

	return (2);
}