#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* layers; } ;
struct TYPE_5__ {TYPE_1__ dp; int /*<<< orphan*/  spa; scalar_t__ hpa; int /*<<< orphan*/  iodc_io; } ;
struct TYPE_6__ {TYPE_2__ mem_kbd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_IO_CIN ; 
 TYPE_3__* PAGE0 ; 
 int /*<<< orphan*/  __pa (int*) ; 
 int* iodc_dbuf ; 
 int* iodc_retbuf ; 
 int /*<<< orphan*/  pdc_lock ; 
 int /*<<< orphan*/  real32_call (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pdc_iodc_getc(void)
{
	int ch;
	int status;
	unsigned long flags;

	/* Bail if no console input device. */
	if (!PAGE0->mem_kbd.iodc_io)
		return 0;
	
	/* wait for a keyboard (rs232)-input */
	spin_lock_irqsave(&pdc_lock, flags);
	real32_call(PAGE0->mem_kbd.iodc_io,
		    (unsigned long)PAGE0->mem_kbd.hpa, ENTRY_IO_CIN,
		    PAGE0->mem_kbd.spa, __pa(PAGE0->mem_kbd.dp.layers), 
		    __pa(iodc_retbuf), 0, __pa(iodc_dbuf), 1, 0);

	ch = *iodc_dbuf;
	status = *iodc_retbuf;
	spin_unlock_irqrestore(&pdc_lock, flags);

	if (status == 0)
	    return -1;
	
	return ch;
}