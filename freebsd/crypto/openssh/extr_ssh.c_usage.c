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
"usage: ssh [-46AaCfGgKkMNnqsTtVvXxYy] [-B bind_interface]\n"
"           [-b bind_address] [-c cipher_spec] [-D [bind_address:]port]\n"
"           [-E log_file] [-e escape_char] [-F configfile] [-I pkcs11]\n"
"           [-i identity_file] [-J [user@]host[:port]] [-L address]\n"
"           [-l login_name] [-m mac_spec] [-O ctl_cmd] [-o option] [-p port]\n"
"           [-Q query_option] [-R address] [-S ctl_path] [-W host:port]\n"
"           [-w local_tun[:remote_tun]] destination [command]\n"
	);
	exit(255);
}