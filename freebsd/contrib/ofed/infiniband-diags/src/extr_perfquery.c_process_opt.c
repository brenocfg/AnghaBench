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
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  ALL_PORTS ; 
 int /*<<< orphan*/  all_ports ; 
 int /*<<< orphan*/  dgid ; 
 int extended ; 
 int extended_speeds ; 
 int flowctlcounters ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ibdiag_show_usage () ; 
 int /*<<< orphan*/  inet_pton (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loop_ports ; 
 int oprcvcounters ; 
 int /*<<< orphan*/  port ; 
 int rcv_err ; 
 int rcv_sl ; 
 int rcvcc ; 
 int /*<<< orphan*/  reset ; 
 int /*<<< orphan*/  reset_only ; 
 int slrcvbecn ; 
 int slrcvfecn ; 
 int smpl_ctl ; 
 int /*<<< orphan*/  stderr ; 
 int swportvlcong ; 
 int vlopdata ; 
 int vloppackets ; 
 int vlxmitcounters ; 
 int vlxmitflowctlerrors ; 
 int vlxmittimecc ; 
 int with_grh ; 
 int xmitcc ; 
 int xmt_disc ; 
 int xmt_sl ; 

__attribute__((used)) static int process_opt(void *context, int ch, char *optarg)
{
	switch (ch) {
	case 'x':
		extended = 1;
		break;
	case 'X':
		xmt_sl = 1;
		break;
	case 'S':
		rcv_sl = 1;
		break;
	case 'D':
		xmt_disc = 1;
		break;
	case 'E':
		rcv_err = 1;
		break;
	case 'T':
		extended_speeds = 1;
		break;
	case 'c':
		smpl_ctl = 1;
		break;
	case 1:
		oprcvcounters = 1;
		break;
	case 2:
		flowctlcounters = 1;
		break;
	case 3:
		vloppackets = 1;
		break;
	case 4:
		vlopdata = 1;
		break;
	case 5:
		vlxmitflowctlerrors = 1;
		break;
	case 6:
		vlxmitcounters = 1;
		break;
	case 7:
		swportvlcong = 1;
		break;
	case 8:
		rcvcc = 1;
		break;
	case 9:
		slrcvfecn = 1;
		break;
	case 10:
		slrcvbecn = 1;
		break;
	case 11:
		xmitcc = 1;
		break;
	case 12:
		vlxmittimecc = 1;
		break;
	case 'a':
		all_ports++;
		port = ALL_PORTS;
		break;
	case 'l':
		loop_ports++;
		break;
	case 'r':
		reset++;
		break;
	case 'R':
		reset_only++;
		break;
	case 25:
		if (!inet_pton(AF_INET6, optarg, &dgid)) {
			fprintf(stderr, "dgid format is wrong!\n");
			ibdiag_show_usage();
			return 1;
		}
		with_grh = 1;
		break;
	default:
		return -1;
	}
	return 0;
}