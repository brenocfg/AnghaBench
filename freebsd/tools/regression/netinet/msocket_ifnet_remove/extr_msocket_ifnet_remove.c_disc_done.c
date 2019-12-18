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
struct ifreq {int /*<<< orphan*/  ifr_name; } ;
typedef  int /*<<< orphan*/  ifr ;

/* Variables and functions */
 char* DISC_IFNAME ; 
 int /*<<< orphan*/  DISC_IFUNIT ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SIOCIFDESTROY ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  bzero (struct ifreq*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static void
disc_done(void)
{
	struct ifreq ifr;
	int s;

	s = socket(PF_INET, SOCK_RAW, 0);
	if (s < 0) {
		warn("disc_done: socket(PF_INET, SOCK_RAW, 0)");
		return;
	}

	bzero(&ifr, sizeof(ifr));
	snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "%s%d", DISC_IFNAME,
	    DISC_IFUNIT);

	if (ioctl(s, SIOCIFDESTROY, &ifr) < 0)
		warn("disc_done: ioctl(%s, SIOCIFDESTROY)", ifr.ifr_name);
	close(s);
}