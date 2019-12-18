#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in {int sin_len; scalar_t__ sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  myaddr ;
struct TYPE_2__ {int /*<<< orphan*/  rip_vers; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ EADDRINUSE ; 
 scalar_t__ IPPORT_RESERVED ; 
 TYPE_1__ OMSG ; 
 int /*<<< orphan*/  RIPv1 ; 
 int /*<<< orphan*/  RIPv2 ; 
 scalar_t__ bind (int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ geteuid () ; 
 void* htons (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ntohs (scalar_t__) ; 
 scalar_t__ out (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ ripv2 ; 
 int /*<<< orphan*/  soc ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
trace_loop(char *argv[])
{
	struct sockaddr_in myaddr;
	int res;

	if (geteuid() != 0) {
		(void)fprintf(stderr, "-t requires UID 0\n");
		exit(1);
	}

	if (ripv2) {
		OMSG.rip_vers = RIPv2;
	} else {
		OMSG.rip_vers = RIPv1;
	}

	memset(&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
#ifdef _HAVE_SIN_LEN
	myaddr.sin_len = sizeof(myaddr);
#endif
	myaddr.sin_port = htons(IPPORT_RESERVED-1);
	while (bind(soc, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		if (errno != EADDRINUSE
		    || myaddr.sin_port == 0) {
			perror("bind");
			exit(2);
		}
		myaddr.sin_port = htons(ntohs(myaddr.sin_port)-1);
	}

	res = 1;
	while (*argv != NULL) {
		if (out(*argv++) <= 0)
			res = 0;
	}
	exit(res);
}