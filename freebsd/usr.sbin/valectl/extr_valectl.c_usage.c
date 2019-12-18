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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(int errcode)
{
	fprintf(stderr,
	    "Usage:\n"
	    "valectl arguments\n"
	    "\t-g interface	interface name to get info\n"
	    "\t-d interface	interface name to be detached\n"
	    "\t-a interface	interface name to be attached\n"
	    "\t-h interface	interface name to be attached with the host stack\n"
	    "\t-n interface	interface name to be created\n"
	    "\t-r interface	interface name to be deleted\n"
	    "\t-l list all or specified bridge's interfaces (default)\n"
	    "\t-C string ring/slot setting of an interface creating by -n\n"
	    "\t-p interface start polling. Additional -C x,y,z configures\n"
	    "\t\t x: 0 (REG_ALL_NIC) or 1 (REG_ONE_NIC),\n"
	    "\t\t y: CPU core id for ALL_NIC and core/ring for ONE_NIC\n"
	    "\t\t z: (ONE_NIC only) num of total cores/rings\n"
	    "\t-P interface stop polling\n"
	    "\t-m memid to use when creating a new interface\n");
	exit(errcode);
}