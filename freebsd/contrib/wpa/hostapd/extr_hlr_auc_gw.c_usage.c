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
 char* default_socket_path ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void usage(void)
{
	printf("HLR/AuC testing gateway for hostapd EAP-SIM/AKA "
	       "database/authenticator\n"
	       "Copyright (c) 2005-2017, Jouni Malinen <j@w1.fi>\n"
	       "\n"
	       "usage:\n"
	       "hlr_auc_gw [-hu] [-s<socket path>] [-g<triplet file>] "
	       "[-m<milenage file>] \\\n"
	       "        [-D<DB file>] [-i<IND len in bits>] [command]\n"
	       "\n"
	       "options:\n"
	       "  -h = show this usage help\n"
	       "  -u = update SQN in Milenage file on exit\n"
	       "  -s<socket path> = path for UNIX domain socket\n"
	       "                    (default: %s)\n"
	       "  -g<triplet file> = path for GSM authentication triplets\n"
	       "  -m<milenage file> = path for Milenage keys\n"
	       "  -D<DB file> = path to SQLite database\n"
	       "  -i<IND len in bits> = IND length for SQN (default: 5)\n"
	       "\n"
	       "If the optional command argument, like "
	       "\"AKA-REQ-AUTH <IMSI>\" is used, a single\n"
	       "command is processed with response sent to stdout. Otherwise, "
	       "hlr_auc_gw opens\n"
	       "a control interface and processes commands sent through it "
	       "(e.g., by EAP server\n"
	       "in hostapd).\n",
	       default_socket_path);
}