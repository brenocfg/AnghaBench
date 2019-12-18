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
struct ucom_softc {int dummy; } ;
struct termios {int c_ospeed; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
ucycom_pre_param(struct ucom_softc *ucom, struct termios *t)
{
	switch (t->c_ospeed) {
		case 600:
		case 1200:
		case 2400:
		case 4800:
		case 9600:
		case 19200:
		case 38400:
		case 57600:
#if 0
		/*
		 * Stock chips only support standard baud rates in the 600 - 57600
		 * range, but higher rates can be achieved using custom firmware.
		 */
		case 115200:
		case 153600:
		case 192000:
#endif
		break;
	default:
		return (EINVAL);
	}
	return (0);
}