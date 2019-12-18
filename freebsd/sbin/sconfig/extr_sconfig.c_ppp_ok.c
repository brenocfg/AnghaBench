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
struct stat {int dummy; } ;
struct ifreq {int /*<<< orphan*/  ifr_name; } ;
typedef  int* caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int N_PPP ; 
 int /*<<< orphan*/  SIOCGIFFLAGS ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  TIOCSETD ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int open (char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
ppp_ok (void)
{
#ifdef __linux__
	int s, p;
	struct ifreq ifr;
	char pttyname[32];
	char *p1, *p2;
	int i, j;
	int ppp_disc = N_PPP;

	/*
	 * Open a socket for doing the ioctl operations.
	 */
	s = socket (AF_INET, SOCK_DGRAM, 0);
	if (s < 0) {
		fprintf (stderr, "Error opening socket.\n");
		return 0;
	}
	strncpy (ifr.ifr_name, "ppp0", sizeof (ifr.ifr_name));
	if (ioctl (s, SIOCGIFFLAGS, (caddr_t) &ifr) >= 0) {
		/* Ok. */
		close (s);
		return 1;
	}
	close (s);

	/* open pseudo-tty and try to set PPP discipline */
	sprintf (pttyname, "/dev/ptyXX");
	p1 = &pttyname[8];
	p2 = &pttyname[9];
	for (i=0; i<16; i++) {
		struct stat stb;

		*p1 = "pqrstuvwxyzabcde"[i];
		*p2 = '0';
		if (stat (pttyname, &stb) < 0)
			continue;
		for (j=0; j<16; j++) {
			*p2 = "0123456789abcdef"[j];
			p = open (pttyname, 2);
			if (p > 0) {
				if (ioctl (p, TIOCSETD, &ppp_disc) < 0) {
					fprintf (stderr, "No PPP discipline in kernel.\n");
					close (p);
					return 0;
				}
				close (p);
				return 1;
			}
		}
	}
	fprintf (stderr, "Cannot get pseudo-tty.\n");
	return 0;
#else
	return 1;
#endif
}