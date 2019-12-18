#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int serial_signals; } ;
typedef  TYPE_1__ MGSLPC_INFO ;

/* Variables and functions */
 int BIT1 ; 
 int BIT7 ; 
 scalar_t__ CHA ; 
 scalar_t__ CHB ; 
 scalar_t__ PVR ; 
 unsigned char PVR_DSR ; 
 unsigned char PVR_RI ; 
 scalar_t__ STAR ; 
 int SerialSignal_CTS ; 
 int SerialSignal_DCD ; 
 int SerialSignal_DSR ; 
 int SerialSignal_DTR ; 
 int SerialSignal_RI ; 
 int SerialSignal_RTS ; 
 scalar_t__ VSTR ; 
 int read_reg (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void get_signals(MGSLPC_INFO *info)
{
	unsigned char status = 0;

	/* preserve RTS and DTR */
	info->serial_signals &= SerialSignal_RTS | SerialSignal_DTR;

	if (read_reg(info, CHB + VSTR) & BIT7)
		info->serial_signals |= SerialSignal_DCD;
	if (read_reg(info, CHB + STAR) & BIT1)
		info->serial_signals |= SerialSignal_CTS;

	status = read_reg(info, CHA + PVR);
	if (!(status & PVR_RI))
		info->serial_signals |= SerialSignal_RI;
	if (!(status & PVR_DSR))
		info->serial_signals |= SerialSignal_DSR;
}