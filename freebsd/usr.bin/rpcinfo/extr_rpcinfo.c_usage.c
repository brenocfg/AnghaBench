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
	fprintf(stderr, "usage: rpcinfo [-m | -s] [host]\n");
#ifdef PORTMAP
	fprintf(stderr, "       rpcinfo -p [host]\n");
#endif
	fprintf(stderr, "       rpcinfo -T netid host prognum [versnum]\n");
	fprintf(stderr, "       rpcinfo -l host prognum versnum\n");
#ifdef PORTMAP
	fprintf(stderr,
"       rpcinfo [-n portnum] -u | -t host prognum [versnum]\n");
#endif
	fprintf(stderr,
"       rpcinfo -a serv_address -T netid prognum [version]\n");
	fprintf(stderr, "       rpcinfo -b prognum versnum\n");
	fprintf(stderr, "       rpcinfo -d [-T netid] prognum versnum\n");
	exit(1);
}