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
typedef  int uint64_t ;
typedef  int u_int ;
typedef  void* device_t ;

/* Variables and functions */
 int UINT8_MAX ; 
 int WD_INTERVAL ; 
 int WD_TO_1SEC ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (void*,char*,int) ; 
 int superio_read (void*,int) ; 
 int /*<<< orphan*/  superio_write (void*,int,int) ; 

__attribute__((used)) static void
wd_func(void *priv, u_int cmd, int *error)
{
	device_t dev = priv;
	uint64_t timeout;
	uint8_t val;


	if (cmd != 0) {
		cmd &= WD_INTERVAL;

		/*
		 * Convert the requested timeout to seconds.
		 * If the timeout is smaller than the minimal supported value
		 * then set it to the minimum.
		 * TODO This hardware actually supports 64ms resolution
		 * when bit 5 of 0x72 is set.  Switch to that resolution when
		 * needed.
		 */
		if (cmd >= WD_TO_1SEC)
			timeout = (uint64_t)1 << (cmd - WD_TO_1SEC);
		else
			timeout = 1;

		/* TODO If timeout is greater than maximum value
		 * that can be specified in seconds, we should
		 * switch the timer to minutes mode by clearing
		 * bit 7 of 0x72 (ensure that bit 5 is also cleared).
		 *
		 * For now, just disable the timer to honor the
		 * watchdog(9) protocol.
		 *
		 * XXX The timeout actually can be up to 65535 units
		 * as it is set via two registers 0x73, LSB, and 0x74,
		 * MSB.  But it is not clear what the protocol for writing
		 * those two registers is.
		 */
		if (timeout <= UINT8_MAX) {
			val = timeout;
			*error = 0;
		} else {
			/* error left unchanged */
			val = 0;
		}
	} else {
		val = 0;
	}
#ifdef DIAGNOSTIC
	if (bootverbose)
		device_printf(dev, "setting timeout to %d\n", val);
#endif
	superio_write(dev, 0x73, val);
	if (superio_read(dev, 0x73) != val)
		superio_write(dev, 0x73, val);
}