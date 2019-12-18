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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* kex_alg_list (char) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	fprintf(stderr,
	    "Usage: kexfuzz [-hcdrv] [-D direction] [-f data_file]\n"
	    "               [-K kex_alg] [-k private_key] [-i packet_index]\n"
	    "\n"
	    "Options:\n"
	    "    -h               Display this help\n"
	    "    -c               Count packets sent during KEX\n"
	    "    -d               Dump mode: record KEX packet to data file\n"
	    "    -r               Replace mode: replace packet with data file\n"
	    "    -v               Turn on verbose logging\n"
	    "    -D S2C|C2S       Packet direction for replacement or dump\n"
	    "    -f data_file     Path to data file for replacement or dump\n"
	    "    -K kex_alg       Name of KEX algorithm to test (see below)\n"
	    "    -k private_key   Path to private key file\n"
	    "    -i packet_index  Index of packet to replace or dump (from 0)\n"
	    "\n"
	    "Available KEX algorithms: %s\n", kex_alg_list(' '));
}