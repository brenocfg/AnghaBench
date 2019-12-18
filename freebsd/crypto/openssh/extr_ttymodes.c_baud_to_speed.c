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
typedef  int /*<<< orphan*/  speed_t ;

/* Variables and functions */
 int /*<<< orphan*/  B0 ; 
 int /*<<< orphan*/  B110 ; 
 int /*<<< orphan*/  B115200 ; 
 int /*<<< orphan*/  B1200 ; 
 int /*<<< orphan*/  B134 ; 
 int /*<<< orphan*/  B14400 ; 
 int /*<<< orphan*/  B150 ; 
 int /*<<< orphan*/  B1800 ; 
 int /*<<< orphan*/  B19200 ; 
 int /*<<< orphan*/  B200 ; 
 int /*<<< orphan*/  B230400 ; 
 int /*<<< orphan*/  B2400 ; 
 int /*<<< orphan*/  B28800 ; 
 int /*<<< orphan*/  B300 ; 
 int /*<<< orphan*/  B38400 ; 
 int /*<<< orphan*/  B4800 ; 
 int /*<<< orphan*/  B50 ; 
 int /*<<< orphan*/  B57600 ; 
 int /*<<< orphan*/  B600 ; 
 int /*<<< orphan*/  B7200 ; 
 int /*<<< orphan*/  B75 ; 
 int /*<<< orphan*/  B76800 ; 
 int /*<<< orphan*/  B9600 ; 
 int /*<<< orphan*/  EXTA ; 
 int /*<<< orphan*/  EXTB ; 

__attribute__((used)) static speed_t
baud_to_speed(int baud)
{
	switch (baud) {
	case 0:
		return B0;
	case 50:
		return B50;
	case 75:
		return B75;
	case 110:
		return B110;
	case 134:
		return B134;
	case 150:
		return B150;
	case 200:
		return B200;
	case 300:
		return B300;
	case 600:
		return B600;
	case 1200:
		return B1200;
	case 1800:
		return B1800;
	case 2400:
		return B2400;
	case 4800:
		return B4800;
	case 9600:
		return B9600;

#ifdef B19200
	case 19200:
		return B19200;
#else /* B19200 */
#ifdef EXTA
	case 19200:
		return EXTA;
#endif /* EXTA */
#endif /* B19200 */

#ifdef B38400
	case 38400:
		return B38400;
#else /* B38400 */
#ifdef EXTB
	case 38400:
		return EXTB;
#endif /* EXTB */
#endif /* B38400 */

#ifdef B7200
	case 7200:
		return B7200;
#endif /* B7200 */
#ifdef B14400
	case 14400:
		return B14400;
#endif /* B14400 */
#ifdef B28800
	case 28800:
		return B28800;
#endif /* B28800 */
#ifdef B57600
	case 57600:
		return B57600;
#endif /* B57600 */
#ifdef B76800
	case 76800:
		return B76800;
#endif /* B76800 */
#ifdef B115200
	case 115200:
		return B115200;
#endif /* B115200 */
#ifdef B230400
	case 230400:
		return B230400;
#endif /* B230400 */
	default:
		return B9600;
	}
}