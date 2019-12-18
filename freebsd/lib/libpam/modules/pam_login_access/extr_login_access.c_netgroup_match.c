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
typedef  int /*<<< orphan*/  domain ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int NO ; 
 int YES ; 
 scalar_t__ getdomainname (char*,int) ; 
 int innetgr (char const*,char const*,char const*,char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
netgroup_match(const char *group, const char *machine, const char *user)
{
    char domain[1024];
    unsigned int i;

    if (getdomainname(domain, sizeof(domain)) != 0 || *domain == '\0') {
	syslog(LOG_ERR, "NIS netgroup support disabled: no NIS domain");
	return (NO);
    }

    /* getdomainname() does not reliably terminate the string */
    for (i = 0; i < sizeof(domain); ++i)
	if (domain[i] == '\0')
	    break;
    if (i == sizeof(domain)) {
	syslog(LOG_ERR, "NIS netgroup support disabled: invalid NIS domain");
	return (NO);
    }

    if (innetgr(group, machine, user, domain) == 1)
	return (YES);
    return (NO);
}