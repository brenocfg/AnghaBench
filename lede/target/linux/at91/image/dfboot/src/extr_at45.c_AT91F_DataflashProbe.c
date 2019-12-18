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
struct TYPE_4__ {int* command; } ;
typedef  TYPE_1__* AT91PS_DataflashDesc ;

/* Variables and functions */
 int /*<<< orphan*/  AT91F_DataFlashGetStatus (TYPE_1__*) ; 
 int /*<<< orphan*/  AT91F_SpiEnable (int) ; 

int AT91F_DataflashProbe(int cs, AT91PS_DataflashDesc pDesc)
{
	AT91F_SpiEnable(cs);
   	AT91F_DataFlashGetStatus(pDesc);
   	return ((pDesc->command[1] == 0xFF)? 0: (pDesc->command[1] & 0x3C));
}