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
struct ifreq {int ifr_flags; int ifr_flagshigh; int /*<<< orphan*/  ifr_name; } ;
struct afswtch {int dummy; } ;
typedef  int /*<<< orphan*/  my_ifr ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  Perror (char const*) ; 
 int /*<<< orphan*/  SIOCSIFFLAGS ; 
 int getifflags (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
setifflags(const char *vname, int value, int s, const struct afswtch *afp)
{
	struct ifreq		my_ifr;
	int flags;

	flags = getifflags(name, s);
	if (value < 0) {
		value = -value;
		flags &= ~value;
	} else
		flags |= value;
	memset(&my_ifr, 0, sizeof(my_ifr));
	(void) strlcpy(my_ifr.ifr_name, name, sizeof(my_ifr.ifr_name));
	my_ifr.ifr_flags = flags & 0xffff;
	my_ifr.ifr_flagshigh = flags >> 16;
	if (ioctl(s, SIOCSIFFLAGS, (caddr_t)&my_ifr) < 0)
		Perror(vname);
}