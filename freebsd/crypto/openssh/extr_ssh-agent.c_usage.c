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
usage(void)
{
	fprintf(stderr,
	    "usage: ssh-agent [-c | -s] [-Ddx] [-a bind_address] [-E fingerprint_hash]\n"
	    "                 [-P pkcs11_whitelist] [-t life] [command [arg ...]]\n"
	    "       ssh-agent [-c | -s] -k\n");
	exit(1);
}