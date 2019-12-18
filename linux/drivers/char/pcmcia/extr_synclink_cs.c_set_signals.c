#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ mode; } ;
struct TYPE_9__ {int serial_signals; TYPE_1__ params; } ;
typedef  TYPE_2__ MGSLPC_INFO ;

/* Variables and functions */
 unsigned char BIT2 ; 
 unsigned char BIT6 ; 
 scalar_t__ CHA ; 
 scalar_t__ MGSL_MODE_ASYNC ; 
 scalar_t__ MODE ; 
 scalar_t__ PVR ; 
 int /*<<< orphan*/  PVR_DTR ; 
 int SerialSignal_DTR ; 
 int SerialSignal_RTS ; 
 int /*<<< orphan*/  clear_reg_bits (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned char read_reg (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  set_reg_bits (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg (TYPE_2__*,scalar_t__,unsigned char) ; 

__attribute__((used)) static void set_signals(MGSLPC_INFO *info)
{
	unsigned char val;

	val = read_reg(info, CHA + MODE);
	if (info->params.mode == MGSL_MODE_ASYNC) {
		if (info->serial_signals & SerialSignal_RTS)
			val &= ~BIT6;
		else
			val |= BIT6;
	} else {
		if (info->serial_signals & SerialSignal_RTS)
			val |= BIT2;
		else
			val &= ~BIT2;
	}
	write_reg(info, CHA + MODE, val);

	if (info->serial_signals & SerialSignal_DTR)
		clear_reg_bits(info, CHA + PVR, PVR_DTR);
	else
		set_reg_bits(info, CHA + PVR, PVR_DTR);
}