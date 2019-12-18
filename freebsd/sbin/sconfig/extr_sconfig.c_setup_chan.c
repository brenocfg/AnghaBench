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
 int E1CLK_INTERNAL ; 
 int E1CLK_RECEIVE ; 
 int E1CLK_RECEIVE_CHAN0 ; 
 int E1CLK_RECEIVE_CHAN1 ; 
 int E1CLK_RECEIVE_CHAN2 ; 
 int E1CLK_RECEIVE_CHAN3 ; 
 int /*<<< orphan*/  SERIAL_ADDDLCI ; 
 int SERIAL_ASYNC ; 
 int /*<<< orphan*/  SERIAL_GETMODE ; 
 int /*<<< orphan*/  SERIAL_HARDRESET ; 
 int SERIAL_HDLC ; 
 int /*<<< orphan*/  SERIAL_RESET ; 
 int /*<<< orphan*/  SERIAL_SETBAUD ; 
 int /*<<< orphan*/  SERIAL_SETCABLEN ; 
 int /*<<< orphan*/  SERIAL_SETCFG ; 
 int /*<<< orphan*/  SERIAL_SETCLK ; 
 int /*<<< orphan*/  SERIAL_SETCRC4 ; 
 int /*<<< orphan*/  SERIAL_SETDEBUG ; 
 int /*<<< orphan*/  SERIAL_SETDIR ; 
 int /*<<< orphan*/  SERIAL_SETDPLL ; 
 int /*<<< orphan*/  SERIAL_SETHIGAIN ; 
 int /*<<< orphan*/  SERIAL_SETINVCLK ; 
 int /*<<< orphan*/  SERIAL_SETINVRCLK ; 
 int /*<<< orphan*/  SERIAL_SETINVTCLK ; 
 int /*<<< orphan*/  SERIAL_SETKEEPALIVE ; 
 int /*<<< orphan*/  SERIAL_SETLCODE ; 
 int /*<<< orphan*/  SERIAL_SETLOOP ; 
 int /*<<< orphan*/  SERIAL_SETMODE ; 
 int /*<<< orphan*/  SERIAL_SETMONITOR ; 
 int /*<<< orphan*/  SERIAL_SETMTU ; 
 int /*<<< orphan*/  SERIAL_SETNRZI ; 
 int /*<<< orphan*/  SERIAL_SETPHONY ; 
 int /*<<< orphan*/  SERIAL_SETPORT ; 
 int /*<<< orphan*/  SERIAL_SETPROTO ; 
 int /*<<< orphan*/  SERIAL_SETRLOOP ; 
 int /*<<< orphan*/  SERIAL_SETRQLEN ; 
 int /*<<< orphan*/  SERIAL_SETSCRAMBLER ; 
 int /*<<< orphan*/  SERIAL_SETSUBCHAN ; 
 int /*<<< orphan*/  SERIAL_SETTIMESLOTS ; 
 int /*<<< orphan*/  SERIAL_SETUNFRAM ; 
 int /*<<< orphan*/  SERIAL_SETUSE16 ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,...) ; 
 scalar_t__ ppp_ok () ; 
 long scan_timeslots (char*) ; 
 int /*<<< orphan*/  set_debug_ifconfig (int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 void* strtol (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
setup_chan (int fd, int argc, char **argv)
{
	int i, mode, loop, nrzi, dpll, invclk, phony, use16, crc4, unfram, ami;
	int higain, clk, keepalive, debug, port, dlci, invrclk, invtclk;
	int monitor, dir, scrambler, rloop, cablen;
	int mode_valid;
	long baud, timeslots, mtu, rqlen;

	for (i=0; i<argc; ++i) {
		if (argv[i][0] >= '0' && argv[i][0] <= '9') {
			baud = strtol (argv[i], 0, 10);
			ioctl (fd, SERIAL_SETBAUD, &baud);
		} else if (strcasecmp ("extclock", argv[i]) == 0) {
			baud = 0;
			ioctl (fd, SERIAL_SETBAUD, &baud);
		} else if (strncasecmp ("cfg=", argv[i], 4) == 0) {
			if (strncasecmp ("a", argv[i]+4, 1) == 0)
				ioctl (fd, SERIAL_SETCFG, "a");
			else if (strncasecmp ("b", argv[i]+4, 1) == 0)
				ioctl (fd, SERIAL_SETCFG, "b");
			else if (strncasecmp ("c", argv[i]+4, 1) == 0)
				ioctl (fd, SERIAL_SETCFG, "c");
			else if (strncasecmp ("d", argv[i]+4, 1) == 0)
				ioctl (fd, SERIAL_SETCFG, "d");
			else {
				fprintf (stderr, "invalid cfg\n");
				exit (-1);
			}
		} else if (strcasecmp ("idle", argv[i]) == 0)
			ioctl (fd, SERIAL_SETPROTO, "\0\0\0\0\0\0\0");
		else if (strcasecmp ("async", argv[i]) == 0) {
			mode = SERIAL_ASYNC;
			if (ioctl (fd, SERIAL_SETMODE, &mode) >= 0)
				ioctl (fd, SERIAL_SETPROTO, "async\0\0");
		} else if (strcasecmp ("sync", argv[i]) == 0) {
			mode = SERIAL_HDLC;
			if (ioctl (fd, SERIAL_SETMODE, &mode) >= 0)
				ioctl (fd, SERIAL_SETPROTO, "sync\0\0\0");
		} else if (strcasecmp ("cisco", argv[i]) == 0) {
			mode = SERIAL_HDLC;
			ioctl (fd, SERIAL_SETMODE, &mode);
			ioctl (fd, SERIAL_SETPROTO, "cisco\0\0");
		} else if (strcasecmp ("rbrg", argv[i]) == 0) {
			mode = SERIAL_HDLC;
			ioctl (fd, SERIAL_SETMODE, &mode);
			ioctl (fd, SERIAL_SETPROTO, "rbrg\0\0\0");
		} else if (strcasecmp ("raw", argv[i]) == 0) {
			mode = SERIAL_HDLC;
			ioctl (fd, SERIAL_SETMODE, &mode);
			ioctl (fd, SERIAL_SETPROTO, "raw\0\0\0\0");
		} else if (strcasecmp ("packet", argv[i]) == 0) {
			mode = SERIAL_HDLC;
			ioctl (fd, SERIAL_SETMODE, &mode);
			ioctl (fd, SERIAL_SETPROTO, "packet\0");
		} else if (strcasecmp ("ppp", argv[i]) == 0) {
			/* check that ppp line discipline is present */
			if (ppp_ok ()) {
				mode = SERIAL_HDLC;
				ioctl (fd, SERIAL_SETMODE, &mode);
				ioctl (fd, SERIAL_SETPROTO, "ppp\0\0\0\0");
			}
		} else if (strncasecmp ("keepalive=", argv[i], 10) == 0) {
			keepalive = (strcasecmp ("on", argv[i] + 10) == 0);
			ioctl (fd, SERIAL_SETKEEPALIVE, &keepalive);
		} else if (strcasecmp ("fr", argv[i]) == 0) {
			mode = SERIAL_HDLC;
			ioctl (fd, SERIAL_SETMODE, &mode);
			ioctl (fd, SERIAL_SETPROTO, "fr\0\0\0\0\0");
		} else if (strcasecmp ("zaptel", argv[i]) == 0) {
			mode = SERIAL_HDLC;
			ioctl (fd, SERIAL_SETMODE, &mode);
			ioctl (fd, SERIAL_SETPROTO, "zaptel\0");
		} else if (strncasecmp ("debug=", argv[i], 6) == 0) {
			debug = strtol (argv[i]+6, 0, 10);
			mode_valid = ioctl (fd, SERIAL_GETMODE, &mode) >= 0;
			if (!mode_valid || mode != SERIAL_ASYNC) {
				if (debug == 0) {
					set_debug_ifconfig(0);
				} else {
					ioctl (fd, SERIAL_SETDEBUG, &debug);
					set_debug_ifconfig(1);
				}
			} else {
				ioctl (fd, SERIAL_SETDEBUG, &debug);
			}
		} else if (strncasecmp ("loop=", argv[i], 5) == 0) {
			loop = (strcasecmp ("on", argv[i] + 5) == 0);
			ioctl (fd, SERIAL_SETLOOP, &loop);
		} else if (strncasecmp ("rloop=", argv[i], 6) == 0) {
			rloop = (strcasecmp ("on", argv[i] + 6) == 0);
			ioctl (fd, SERIAL_SETRLOOP, &rloop);
		} else if (strncasecmp ("dpll=", argv[i], 5) == 0) {
			dpll = (strcasecmp ("on", argv[i] + 5) == 0);
			ioctl (fd, SERIAL_SETDPLL, &dpll);
		} else if (strncasecmp ("nrzi=", argv[i], 5) == 0) {
			nrzi = (strcasecmp ("on", argv[i] + 5) == 0);
			ioctl (fd, SERIAL_SETNRZI, &nrzi);
		} else if (strncasecmp ("invclk=", argv[i], 7) == 0) {
			invclk = (strcasecmp ("on", argv[i] + 7) == 0);
			ioctl (fd, SERIAL_SETINVCLK, &invclk);
		} else if (strncasecmp ("invrclk=", argv[i], 8) == 0) {
			invrclk = (strcasecmp ("on", argv[i] + 8) == 0);
			ioctl (fd, SERIAL_SETINVRCLK, &invrclk);
		} else if (strncasecmp ("invtclk=", argv[i], 8) == 0) {
			invtclk = (strcasecmp ("on", argv[i] + 8) == 0);
			ioctl (fd, SERIAL_SETINVTCLK, &invtclk);
		} else if (strncasecmp ("higain=", argv[i], 7) == 0) {
			higain = (strcasecmp ("on", argv[i] + 7) == 0);
			ioctl (fd, SERIAL_SETHIGAIN, &higain);
		} else if (strncasecmp ("phony=", argv[i], 6) == 0) {
			phony = (strcasecmp ("on", argv[i] + 6) == 0);
			ioctl (fd, SERIAL_SETPHONY, &phony);
		} else if (strncasecmp ("unfram=", argv[i], 7) == 0) {
			unfram = (strcasecmp ("on", argv[i] + 7) == 0);
			ioctl (fd, SERIAL_SETUNFRAM, &unfram);
		} else if (strncasecmp ("scrambler=", argv[i], 10) == 0) {
			scrambler = (strcasecmp ("on", argv[i] + 10) == 0);
			ioctl (fd, SERIAL_SETSCRAMBLER, &scrambler);
		} else if (strncasecmp ("monitor=", argv[i], 8) == 0) {
			monitor = (strcasecmp ("on", argv[i] + 8) == 0);
			ioctl (fd, SERIAL_SETMONITOR, &monitor);
		} else if (strncasecmp ("use16=", argv[i], 6) == 0) {
			use16 = (strcasecmp ("on", argv[i] + 6) == 0);
			ioctl (fd, SERIAL_SETUSE16, &use16);
		} else if (strncasecmp ("crc4=", argv[i], 5) == 0) {
			crc4 = (strcasecmp ("on", argv[i] + 5) == 0);
			ioctl (fd, SERIAL_SETCRC4, &crc4);
		} else if (strncasecmp ("ami=", argv[i], 4) == 0) {
			ami = (strcasecmp ("on", argv[i] + 4) == 0);
			ioctl (fd, SERIAL_SETLCODE, &ami);
		} else if (strncasecmp ("mtu=", argv[i], 4) == 0) {
			mtu = strtol (argv[i] + 4, 0, 10);
			ioctl (fd, SERIAL_SETMTU, &mtu);
		} else if (strncasecmp ("rqlen=", argv[i], 6) == 0) {
			rqlen = strtol (argv[i] + 6, 0, 10);
			ioctl (fd, SERIAL_SETRQLEN, &rqlen);
		} else if (strcasecmp ("syn=int", argv[i]) == 0) {
			clk = E1CLK_INTERNAL;
			ioctl (fd, SERIAL_SETCLK, &clk);
		} else if (strcasecmp ("syn=rcv", argv[i]) == 0) {
			clk = E1CLK_RECEIVE;
			ioctl (fd, SERIAL_SETCLK, &clk);
		} else if (strcasecmp ("syn=rcv0", argv[i]) == 0) {
			clk = E1CLK_RECEIVE_CHAN0;
			ioctl (fd, SERIAL_SETCLK, &clk);
		} else if (strcasecmp ("syn=rcv1", argv[i]) == 0) {
			clk = E1CLK_RECEIVE_CHAN1;
			ioctl (fd, SERIAL_SETCLK, &clk);
		} else if (strcasecmp ("syn=rcv2", argv[i]) == 0) {
			clk = E1CLK_RECEIVE_CHAN2;
			ioctl (fd, SERIAL_SETCLK, &clk);
		} else if (strcasecmp ("syn=rcv3", argv[i]) == 0) {
			clk = E1CLK_RECEIVE_CHAN3;
			ioctl (fd, SERIAL_SETCLK, &clk);
		} else if (strncasecmp ("ts=", argv[i], 3) == 0) {
			timeslots = scan_timeslots (argv[i] + 3);
			ioctl (fd, SERIAL_SETTIMESLOTS, &timeslots);
		} else if (strncasecmp ("pass=", argv[i], 5) == 0) {
			timeslots = scan_timeslots (argv[i] + 5);
			ioctl (fd, SERIAL_SETSUBCHAN, &timeslots);
		} else if (strncasecmp ("dlci", argv[i], 4) == 0) {
			dlci = strtol (argv[i]+4, 0, 10);
			ioctl (fd, SERIAL_ADDDLCI, &dlci);
		} else if (strncasecmp ("dir=", argv[i], 4) == 0) {
			dir = strtol (argv[i]+4, 0, 10);
			ioctl (fd, SERIAL_SETDIR, &dir);
		} else if (strncasecmp ("port=", argv[i], 5) == 0) {
			if (strncasecmp ("rs232", argv[i]+5, 5) == 0) {
				port = 0;
				ioctl (fd, SERIAL_SETPORT, &port);
			} else if (strncasecmp ("v35", argv[i]+5, 3) == 0) {
				port = 1;
				ioctl (fd, SERIAL_SETPORT, &port);
			} else if (strncasecmp ("rs449", argv[i]+5, 5) == 0) {
				port = 2;
				ioctl (fd, SERIAL_SETPORT, &port);
			} else
				fprintf (stderr, "invalid port type\n");
				exit (-1);
#if 1
		} else if (strcasecmp ("reset", argv[i]) == 0) {
			ioctl (fd, SERIAL_RESET, 0);
		} else if (strcasecmp ("hwreset", argv[i]) == 0) {
			ioctl (fd, SERIAL_HARDRESET, 0);
#endif
		} else if (strncasecmp ("cablen=", argv[i], 7) == 0) {
			loop = (strcasecmp ("on", argv[i] + 7) == 0);
			ioctl (fd, SERIAL_SETCABLEN, &cablen);
		}
	}
}