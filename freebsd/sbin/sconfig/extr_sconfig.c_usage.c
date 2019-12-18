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
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
usage (void)
{
	printf(
"Serial Adapter Configuration Utility\n"
"Copyright (C) 1998-2005 Cronyx Engineering.\n"
"See also man sconfig (8)\n"
"Usage:\n"
"\tsconfig [-aimsxeftuc] [device [parameters ...]]\n"
"\n"
"Options:\n"
"\t<no options>\t\t -- print channel options\n"
"\t-a\t\t\t -- print all settings of the channel\n"
"\t-i\t\t\t -- print network interface status\n"
"\t-m\t\t\t -- print modem signal status\n"
"\t-s\t\t\t -- print channel statistics\n"
"\t-x\t\t\t -- print extended channel statistics\n"
"\t-e\t\t\t -- print short E1/G703 statistics\n"
"\t-f\t\t\t -- print full E1/G703 statistics\n"
"\t-t\t\t\t -- print short E3/T3/STS-1 statistics\n"
"\t-u\t\t\t -- print full E3/T3/STS-1 statistics\n"
"\t-c\t\t\t -- clear statistics\n"
"\nParameters:\n"
"\t<number>\t\t -- baud rate, internal clock\n"
"\textclock\t\t -- external clock (default)\n"
"\nProtocol options:\n"
"\tasync\t\t\t -- asynchronous protocol\n"
#ifdef __linux__
"\tsync\t\t\t -- synchronous protocol\n"
#endif
"\tcisco\t\t\t -- Cisco/HDLC protocol\n"
"\tfr\t\t\t -- Frame Relay protocol\n"
#ifdef __linux__
"\t    dlci<number>\t -- Add new DLCI\n"
#endif
"\tppp\t\t\t -- PPP protocol\n"
#ifdef __linux__
"\trbrg\t\t\t -- Remote bridge\n"
"\traw\t\t\t -- raw HDLC protocol\n"
"\tpacket\t\t\t -- packetized HDLC protocol\n"
"\tidle\t\t\t -- no protocol\n"
#else
"\t    keepalive={on,of}\t -- Enable/disable keepalive\n"
#endif
"\nInterface options:\n"
"\tport={rs232,v35,rs449}\t -- port type (for old models of Sigma)\n"
"\tcfg={A,B,C}\t\t -- adapter configuration\n"
"\tloop={on,off}\t\t -- internal loopback\n"
"\trloop={on,off}\t\t -- remote loopback\n"
"\tdpll={on,off}\t\t -- DPLL mode\n"
"\tnrzi={on,off}\t\t -- NRZI encoding\n"
"\tinvclk={on,off}\t\t -- invert receive and transmit clock\n"
"\tinvrclk={on,off}\t -- invert receive clock\n"
"\tinvtclk={on,off}\t -- invert transmit clock\n"
"\thigain={on,off}\t\t -- E1 high non linear input sensitivity \n\t\t\t\t    (long line)\n"
"\tmonitor={on,off}\t -- E1 high linear input sensitivity \n\t\t\t\t    (interception mode)\n"
"\tphony={on,off}\t\t -- E1 telepnony mode\n"
"\tunfram={on,off}\t\t -- E1 unframed mode\n"
"\tscrambler={on,off}\t -- G.703 scrambling mode\n"
"\tuse16={on,off}\t\t -- E1 timeslot 16 usage\n"
"\tcrc4={on,off}\t\t -- E1 CRC4 mode\n"
#ifdef __linux__
"\tami={on,off}\t\t -- E1 AMI or HDB3 line code\n"
"\tmtu={size}\t\t -- set MTU in bytes\n"
#endif
"\tsyn={int,rcv,rcvX}\t -- G.703 transmit clock\n"
"\tts=...\t\t\t -- E1 timeslots\n"
"\tpass=...\t\t -- E1 subchannel timeslots\n"
"\tdir=<num>\t\t -- connect channel to link<num>\n"
/*"\trqken={size}\t\t -- set receive queue length in packets\n"*/
/*"\tcablen={on,off}\t\t -- T3/STS-1 high transmitter output for long cable\n"*/
"\tdebug={0,1,2}\t\t -- enable/disable debug messages\n"
	);
	exit (0);
}