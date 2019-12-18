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

/* Variables and functions */
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 char* getprogname () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	fputs(getprogname(), stderr);
	fputs(" - communicate on SPI bus with slave devices\n"
	      "Usage:\n"
	      "        spi [-f device] [-d r|w|rw] [-m mode] [-s max-speed] [-c count]\n"
	      "            [-C \"command bytes\"] [-A] [-b] [-L] [-v]\n"
	      "        spi -i [-f device] [-v]\n"
	      "        spi -h\n"
	      " where\n"
	      "        -f specifies the device (default is spigen0.0)\n"
	      "        -d specifies the operation (r, w, or rw; default is rw)\n"
	      "        -m specifies the mode (0, 1, 2, or 3)\n"
	      "        -s specifies the maximum speed (default is 0, device default)\n"
	      "        -c specifies the number of data bytes to transfer (default 0, i.e. none)\n"
	      "           A negative value uses the length of the input data\n"
	      "        -C specifies 'command bytes' to be sent, as 2 byte hexadecimal values\n"
	      "           (these should be quoted, separated by optional white space)\n"
	      "        -L specifies 'LSB' order on the SPI bus (default is MSB)\n"
	      "        -i query information about the device\n"
	      "        -A uses ASCII for input/output as 2-digit hex values\n"
	      "        -b Override output format as binary (only valid with '-A')\n"
	      "        -v verbose output\n"
	      "        -h prints this message\n"
	      "\n"
	      "NOTE:  setting the mode and/or speed is 'sticky'.  Subsequent transactions\n"
	      "       on that device will, by default, use the previously set values.\n"
	      "\n",
	      stderr);
}