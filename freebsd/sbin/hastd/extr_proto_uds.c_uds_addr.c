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
struct sockaddr_un {int /*<<< orphan*/  sun_len; int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int ENAMETOOLONG ; 
 int /*<<< orphan*/  SUN_LEN (struct sockaddr_un*) ; 
 int strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 

__attribute__((used)) static int
uds_addr(const char *addr, struct sockaddr_un *sunp)
{

	if (addr == NULL)
		return (-1);

	if (strncasecmp(addr, "uds://", 6) == 0)
		addr += 6;
	else if (strncasecmp(addr, "unix://", 7) == 0)
		addr += 7;
	else if (addr[0] == '/' &&	/* If it starts from /... */
	    strstr(addr, "://") == NULL)/* ...and there is no prefix... */
		;			/* ...we assume its us. */
	else
		return (-1);

	sunp->sun_family = AF_UNIX;
	if (strlcpy(sunp->sun_path, addr, sizeof(sunp->sun_path)) >=
	    sizeof(sunp->sun_path)) {
		return (ENAMETOOLONG);
	}
	sunp->sun_len = SUN_LEN(sunp);

	return (0);
}