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
struct termios {int dummy; } ;
typedef  int /*<<< orphan*/  speed_t ;

/* Variables and functions */
 int /*<<< orphan*/  cfgetispeed (struct termios*) ; 
 int /*<<< orphan*/  cfgetospeed (struct termios*) ; 

__attribute__((used)) static speed_t
tty__getspeed(struct termios *td)
{
	speed_t spd;

	if ((spd = cfgetispeed(td)) == 0)
		spd = cfgetospeed(td);
	return spd;
}