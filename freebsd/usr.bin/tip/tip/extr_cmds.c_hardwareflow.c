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
struct termios {int /*<<< orphan*/  c_iflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTSCTS ; 
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  TCSADRAIN ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 

__attribute__((used)) static void
hardwareflow(char *option)
{
	struct termios	rmtty;

	tcgetattr(FD, &rmtty);
	if (strcmp(option, "on") == 0)
		rmtty.c_iflag |= CRTSCTS;
	else
		rmtty.c_iflag &= ~CRTSCTS;
	tcsetattr(FD, TCSADRAIN, &rmtty);
}