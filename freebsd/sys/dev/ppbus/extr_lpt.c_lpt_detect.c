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
typedef  int u_char ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PPB_DONTWAIT ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lpt_port_test (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  lpt_release_ppbus (int /*<<< orphan*/ ) ; 
 int lpt_request_ppbus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wctr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wdtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpt_detect(device_t dev)
{
	device_t ppbus = device_get_parent(dev);

	static u_char	testbyte[18] = {
		0x55,			/* alternating zeros */
		0xaa,			/* alternating ones */
		0xfe, 0xfd, 0xfb, 0xf7,
		0xef, 0xdf, 0xbf, 0x7f,	/* walking zero */
		0x01, 0x02, 0x04, 0x08,
		0x10, 0x20, 0x40, 0x80	/* walking one */
	};
	int		i, error, status;

	status = 1;				/* assume success */

	ppb_lock(ppbus);
	if ((error = lpt_request_ppbus(dev, PPB_DONTWAIT))) {
		ppb_unlock(ppbus);
		device_printf(dev, "cannot alloc ppbus (%d)!\n", error);
		return (0);
	}

	for (i = 0; i < 18 && status; i++)
		if (!lpt_port_test(ppbus, testbyte[i], 0xff)) {
			status = 0;
			break;
		}

	/* write 0's to control and data ports */
	ppb_wdtr(ppbus, 0);
	ppb_wctr(ppbus, 0);

	lpt_release_ppbus(dev);
	ppb_unlock(ppbus);

	return (status);
}