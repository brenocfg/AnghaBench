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
struct TYPE_4__ {unsigned short imra_value; unsigned short imrb_value; } ;
typedef  TYPE_1__ MGSLPC_INFO ;

/* Variables and functions */
 unsigned char CHA ; 
 scalar_t__ CHB ; 
 scalar_t__ IMR ; 
 int /*<<< orphan*/  write_reg16 (TYPE_1__*,scalar_t__,unsigned short) ; 

__attribute__((used)) static void irq_enable(MGSLPC_INFO *info, unsigned char channel, unsigned short mask)
{
	if (channel == CHA) {
		info->imra_value &= ~mask;
		write_reg16(info, CHA + IMR, info->imra_value);
	} else {
		info->imrb_value &= ~mask;
		write_reg16(info, CHB + IMR, info->imrb_value);
	}
}