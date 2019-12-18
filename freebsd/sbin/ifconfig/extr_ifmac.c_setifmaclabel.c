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
struct TYPE_2__ {void* ifru_data; } ;
struct ifreq {TYPE_1__ ifr_ifru; int /*<<< orphan*/  ifr_name; } ;
struct afswtch {int dummy; } ;
typedef  scalar_t__ mac_t ;
typedef  int /*<<< orphan*/  ifr ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCSIFMAC ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  mac_free (scalar_t__) ; 
 int mac_from_text (scalar_t__*,char const*) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
setifmaclabel(const char *val, int d, int s, const struct afswtch *rafp)
{
	struct ifreq ifr;
	mac_t label;
	int error;

	if (mac_from_text(&label, val) == -1) {
		perror(val);
		return;
	}

	memset(&ifr, 0, sizeof(ifr));
	strlcpy(ifr.ifr_name, name, sizeof(ifr.ifr_name));
	ifr.ifr_ifru.ifru_data = (void *)label;

	error = ioctl(s, SIOCSIFMAC, &ifr);
	mac_free(label);
	if (error == -1)
		perror("setifmac");
}