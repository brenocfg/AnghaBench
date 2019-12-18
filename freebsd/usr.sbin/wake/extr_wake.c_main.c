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
typedef  int /*<<< orphan*/  ifname ;

/* Variables and functions */
 int IF_NAMESIZE ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  _PATH_BPF ; 
 int bind_if_to_bpf (char*,int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ find_ether (char*,int) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ wake (int,char*) ; 
 int /*<<< orphan*/  warn (char*,char*,char*) ; 

int
main(int argc, char *argv[])
{
	int bpf, n, rval;
	char ifname[IF_NAMESIZE];

	if (argc < 2)
		usage();

	if ((bpf = open(_PATH_BPF, O_RDWR)) == -1)
		err(1, "Cannot open bpf interface");

	n = 2;
	if (bind_if_to_bpf(argv[1], bpf) == -1) {
		if (find_ether(ifname, sizeof(ifname)))
			err(1, "Failed to determine ethernet interface");
		if (bind_if_to_bpf(ifname, bpf) == -1)
			err(1, "Cannot bind to interface `%s'", ifname);
		--n;
	} else
		strlcpy(ifname, argv[1], sizeof(ifname));

	if (n >= argc)
		usage();
	rval = 0;
	for (; n < argc; n++) {
		if (wake(bpf, argv[n]) != 0) {
			rval = 1;
			warn("Cannot send Wake on LAN frame over `%s' to `%s'",
			    ifname, argv[n]);
		}
	}
	exit(rval);
}