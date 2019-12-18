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
typedef  int /*<<< orphan*/  u32 ;
struct serial_console_data {int /*<<< orphan*/  close; int /*<<< orphan*/  putc; int /*<<< orphan*/  open; } ;

/* Variables and functions */
 scalar_t__ be32_to_cpu (scalar_t__) ; 
 int getprop (void*,char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  opal_con_close ; 
 scalar_t__ opal_con_id ; 
 int /*<<< orphan*/  opal_con_open ; 
 int /*<<< orphan*/  opal_con_putc ; 
 int /*<<< orphan*/  opal_init () ; 

int opal_console_init(void *devp, struct serial_console_data *scdp)
{
	opal_init();

	if (devp) {
		int n = getprop(devp, "reg", &opal_con_id, sizeof(u32));
		if (n != sizeof(u32))
			return -1;
		opal_con_id = be32_to_cpu(opal_con_id);
	} else
		opal_con_id = 0;

	scdp->open = opal_con_open;
	scdp->putc = opal_con_putc;
	scdp->close = opal_con_close;

	return 0;
}