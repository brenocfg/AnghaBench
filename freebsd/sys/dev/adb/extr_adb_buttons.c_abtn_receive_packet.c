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
typedef  int u_int ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  devctl_notify (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static u_int
abtn_receive_packet(device_t dev, u_char status, 
    u_char command, u_char reg, int len, u_char *data)
{
	u_int cmd;

	cmd = data[0];

	switch (cmd) {
	case 0x0a:	/* decrease brightness */
		devctl_notify("PMU", "keys", "brightness",
		    "notify=down");
		break;

	case 0x09:	/* increase brightness */
		devctl_notify("PMU", "keys", "brightness", "notify=up");
		break;

	case 0x08:	/* mute */
	case 0x01:	/* mute, AV hardware */
		devctl_notify("PMU", "keys", "mute", NULL);
		break;
	case 0x07:	/* decrease volume */
	case 0x02:	/* decrease volume, AV hardware */
		devctl_notify("PMU", "keys", "volume", "notify=down");
		break;
	case 0x06:	/* increase volume */
	case 0x03:	/* increase volume, AV hardware */
		devctl_notify("PMU", "keys", "volume", "notify=up");
		break;
	case 0x0c:	/* mirror display key */
		/* Need callback to do something with this */
		break;
	case 0x0b:	/* eject tray */
		devctl_notify("PMU", "keys", "eject", NULL);
		break;
	case 0x7f:	/* numlock */
		/* Need callback to do something with this */
		break;

	default:
#ifdef DEBUG
		if ((cmd & ~0x7f) == 0)
			device_printf(dev, "unknown ADB button 0x%x\n", cmd);
#endif
		break;
	}
	return 0;
}