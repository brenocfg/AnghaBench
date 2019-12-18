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
typedef  int /*<<< orphan*/  hostname ;

/* Variables and functions */
 int /*<<< orphan*/  MAXHOSTNAMELEN ; 
 scalar_t__ MAXNETNAMELEN ; 
 char* OPSYS ; 
 scalar_t__ __rpc_get_default_domain (char**) ; 
 int /*<<< orphan*/  gethostname (char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char const*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

int
host2netname(char netname[MAXNETNAMELEN + 1], const char *host, const char *domain)
{
	char *dfltdom;
	char hostname[MAXHOSTNAMELEN+1];

	if (domain == NULL) {
		if (__rpc_get_default_domain(&dfltdom) != 0) {
			return (0);
		}
		domain = dfltdom;
	}
	if (host == NULL) {
		(void) gethostname(hostname, sizeof(hostname));
		host = hostname;
	}
	if (strlen(domain) + 1 + strlen(host) + 1 + strlen(OPSYS) > MAXNETNAMELEN) {
		return (0);
	} 
	(void) sprintf(netname, "%s.%s@%s", OPSYS, host, domain);
	return (1);
}