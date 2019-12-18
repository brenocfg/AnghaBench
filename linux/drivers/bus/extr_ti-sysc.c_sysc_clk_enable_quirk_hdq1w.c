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
typedef  int /*<<< orphan*/  u16 ;
struct sysc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  sysc_read (struct sysc*,int) ; 
 int /*<<< orphan*/  sysc_write (struct sysc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sysc_clk_enable_quirk_hdq1w(struct sysc *ddata)
{
	int offset = 0x0c;	/* HDQ_CTRL_STATUS */
	u16 val;

	val = sysc_read(ddata, offset);
	val |= BIT(5);
	sysc_write(ddata, offset, val);
}