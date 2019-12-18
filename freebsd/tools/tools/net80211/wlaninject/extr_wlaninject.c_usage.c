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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

void usage(char *progname)
{
	printf("Usage: %s <opts>\n"
		"Physical:\n"
		"\t-i\t<iface>\n"
		"\t-c\t<chan>\n"
		"\t-N\tno ack\n"
		"\t-V\t<iface> [verify via iface whether packet was mangled]\n"
		"\t-W\tWME AC\n"
		"\t-X\ttransmit rate (Mbps)\n"
		"\t-P\ttransmit power (device units)\n"
		"802.11:\n"
		"\t-h\tthis lame message\n"
		"\t-v\t<version>\n"
		"\t-t\t<type>\n"
		"\t-s\t<subtype>\n"
		"\t-T\tto ds\n"
		"\t-F\tfrom ds\n"
		"\t-m\tmore frags\n"
		"\t-r\tretry\n"
		"\t-p\tpower\n"
		"\t-d\tmore data\n"
		"\t-w\twep\n"
		"\t-o\torder\n"
		"\t-u\t<duration>\n"
		"\t-1\t<addr 1>\n"
		"\t-2\t<addr 2>\n"
		"\t-3\t<addr 3>\n"
		"\t-n\t<seqno>\n"
		"\t-f\t<fragno>\n"
		"\t-4\t<addr 4>\n"
		"\t-b\t<payload file>\n"
		"\t-l\t<len>\n"
		"Management:\n"
		"\t-e\t<info element [hex digits 010203... first is type]>\n"
		"\t-S\t<SSID>\n"
		"\t-a\t<algo no>\n"
		"\t-A\t<transaction>\n"
		"\t-C\t<status code>\n"
		"\t-R\tstandard rates\n"
	       , progname);	
	exit(1);	
}