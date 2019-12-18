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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int NO_RECOVERY ; 
 int dns_getaddrinfo (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dns_gethostbyaddr (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dns_gethostbyname (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dns_getnameinfo (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
dns_command(const char *cmd, const nvlist_t *limits, nvlist_t *nvlin,
    nvlist_t *nvlout)
{
	int error;

	if (strcmp(cmd, "gethostbyname") == 0)
		error = dns_gethostbyname(limits, nvlin, nvlout);
	else if (strcmp(cmd, "gethostbyaddr") == 0)
		error = dns_gethostbyaddr(limits, nvlin, nvlout);
	else if (strcmp(cmd, "getnameinfo") == 0)
		error = dns_getnameinfo(limits, nvlin, nvlout);
	else if (strcmp(cmd, "getaddrinfo") == 0)
		error = dns_getaddrinfo(limits, nvlin, nvlout);
	else
		error = NO_RECOVERY;

	return (error);
}