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
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_2__ {int /*<<< orphan*/  dom_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ MAX_RETRIES ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* broad_domain ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 scalar_t__ retries ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ tell_parent (int /*<<< orphan*/ ,struct sockaddr_in*) ; 
 scalar_t__ verify (int /*<<< orphan*/ ) ; 
 scalar_t__ yp_restricted ; 

__attribute__((used)) static bool_t
broadcast_result(bool_t *out, struct sockaddr_in *addr)
{
	if (retries >= MAX_RETRIES) {
		bzero(addr, sizeof(struct sockaddr_in));
		if (tell_parent(broad_domain->dom_domain, addr))
			syslog(LOG_WARNING, "lost connection to parent");
		return (TRUE);
	}

	if (yp_restricted && verify(addr->sin_addr)) {
		retries++;
		syslog(LOG_NOTICE, "NIS server at %s not in restricted mode access list -- rejecting.\n",inet_ntoa(addr->sin_addr));
		return (FALSE);
	} else {
		if (tell_parent(broad_domain->dom_domain, addr))
			syslog(LOG_WARNING, "lost connection to parent");
		return (TRUE);
	}
}