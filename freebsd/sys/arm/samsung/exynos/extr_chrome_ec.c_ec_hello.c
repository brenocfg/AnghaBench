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

/* Variables and functions */
 int /*<<< orphan*/  EC_CMD_HELLO ; 
 int /*<<< orphan*/  ec_command (int /*<<< orphan*/ ,int*,int,int*,int) ; 

int ec_hello(void)
{
	uint8_t data_in[4];
	uint8_t data_out[4];

	data_in[0] = 0x40;
	data_in[1] = 0x30;
	data_in[2] = 0x20;
	data_in[3] = 0x10;

	ec_command(EC_CMD_HELLO, data_in, 4,
	    data_out, 4);

	return (0);
}