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
struct ifreq {scalar_t__ ifr_data; int /*<<< orphan*/  ifr_name; } ;
struct an_req {int dummy; } ;
typedef  int /*<<< orphan*/  ifr ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  SIOCSAIRONET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  bzero (struct ifreq*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
an_setval(const char *iface, struct an_req *areq)
{
	struct ifreq		ifr;
	int			s;

	bzero(&ifr, sizeof(ifr));

	strlcpy(ifr.ifr_name, iface, sizeof(ifr.ifr_name));
	ifr.ifr_data = (caddr_t)areq;

	s = socket(AF_INET, SOCK_DGRAM, 0);

	if (s == -1)
		err(1, "socket");

	if (ioctl(s, SIOCSAIRONET, &ifr) == -1)
		err(1, "SIOCSAIRONET");

	close(s);

	return;
}