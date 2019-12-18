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
typedef  int speed_t ;

/* Variables and functions */
#define  B0 152 
#define  B110 151 
#define  B115200 150 
#define  B1200 149 
#define  B134 148 
#define  B14400 147 
#define  B150 146 
#define  B1800 145 
#define  B19200 144 
#define  B200 143 
#define  B230400 142 
#define  B2400 141 
#define  B28800 140 
#define  B300 139 
#define  B38400 138 
#define  B4800 137 
#define  B50 136 
#define  B57600 135 
#define  B600 134 
#define  B7200 133 
#define  B75 132 
#define  B76800 131 
#define  B9600 130 
#define  EXTA 129 
#define  EXTB 128 

__attribute__((used)) static int
speed_to_baud(speed_t speed)
{
	switch (speed) {
	case B0:
		return 0;
	case B50:
		return 50;
	case B75:
		return 75;
	case B110:
		return 110;
	case B134:
		return 134;
	case B150:
		return 150;
	case B200:
		return 200;
	case B300:
		return 300;
	case B600:
		return 600;
	case B1200:
		return 1200;
	case B1800:
		return 1800;
	case B2400:
		return 2400;
	case B4800:
		return 4800;
	case B9600:
		return 9600;

#ifdef B19200
	case B19200:
		return 19200;
#else /* B19200 */
#ifdef EXTA
	case EXTA:
		return 19200;
#endif /* EXTA */
#endif /* B19200 */

#ifdef B38400
	case B38400:
		return 38400;
#else /* B38400 */
#ifdef EXTB
	case EXTB:
		return 38400;
#endif /* EXTB */
#endif /* B38400 */

#ifdef B7200
	case B7200:
		return 7200;
#endif /* B7200 */
#ifdef B14400
	case B14400:
		return 14400;
#endif /* B14400 */
#ifdef B28800
	case B28800:
		return 28800;
#endif /* B28800 */
#ifdef B57600
	case B57600:
		return 57600;
#endif /* B57600 */
#ifdef B76800
	case B76800:
		return 76800;
#endif /* B76800 */
#ifdef B115200
	case B115200:
		return 115200;
#endif /* B115200 */
#ifdef B230400
	case B230400:
		return 230400;
#endif /* B230400 */
	default:
		return 9600;
	}
}