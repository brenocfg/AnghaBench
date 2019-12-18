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
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCAIFADDR ; 
 int ifaddr_ad (int /*<<< orphan*/ ,char const*,struct sockaddr*,struct sockaddr*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
ifaddr_add(const char *ifnam, struct sockaddr *sa, struct sockaddr *mask)
{
	int error;

	error = ifaddr_ad(SIOCAIFADDR, ifnam, sa, mask);
	if (error != 0)
		warn("ioctl SIOCAIFADDR");
	return (error);
}