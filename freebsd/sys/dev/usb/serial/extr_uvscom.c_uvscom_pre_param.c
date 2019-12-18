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
#define  B115200 138 
#define  B1200 137 
#define  B150 136 
#define  B19200 135 
#define  B2400 134 
#define  B300 133 
#define  B38400 132 
#define  B4800 131 
#define  B57600 130 
#define  B600 129 
#define  B9600 128 
 int EINVAL ; 

__attribute__((used)) static int
uvscom_pre_param(struct ucom_softc *ucom, struct termios *t)
{
	switch (t->c_ospeed) {
		case B150:
		case B300:
		case B600:
		case B1200:
		case B2400:
		case B4800:
		case B9600:
		case B19200:
		case B38400:
		case B57600:
		case B115200:
		default:
		return (EINVAL);
	}
	return (0);
}