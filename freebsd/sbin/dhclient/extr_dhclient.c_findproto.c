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
struct sockaddr {int sa_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE (char*,struct sockaddr*) ; 
 int AF_INET ; 
 int AF_INET6 ; 
#define  RTA_DST 132 
#define  RTA_GATEWAY 131 
#define  RTA_IFA 130 
#define  RTA_IFP 129 
#define  RTA_NETMASK 128 

int
findproto(char *cp, int n)
{
	struct sockaddr *sa;
	unsigned i;

	if (n == 0)
		return -1;
	for (i = 1; i; i <<= 1) {
		if (i & n) {
			sa = (struct sockaddr *)cp;
			switch (i) {
			case RTA_IFA:
			case RTA_DST:
			case RTA_GATEWAY:
			case RTA_NETMASK:
				if (sa->sa_family == AF_INET)
					return AF_INET;
				if (sa->sa_family == AF_INET6)
					return AF_INET6;
				break;
			case RTA_IFP:
				break;
			}
			ADVANCE(cp, sa);
		}
	}
	return (-1);
}