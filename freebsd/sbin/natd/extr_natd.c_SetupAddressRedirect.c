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
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct alias_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INADDR_NONE ; 
 int /*<<< orphan*/  LibAliasAddServer (int /*<<< orphan*/ ,struct alias_link*,struct in_addr,int /*<<< orphan*/ ) ; 
 struct alias_link* LibAliasRedirectAddr (int /*<<< orphan*/ ,struct in_addr,struct in_addr) ; 
 int /*<<< orphan*/  StrToAddr (char*,struct in_addr*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mla ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 char* strtok (char*,char*) ; 

void SetupAddressRedirect (const char* parms)
{
	char		*buf;
	char*		ptr;
	char*		separator;
	struct in_addr	localAddr;
	struct in_addr	publicAddr;
	char*		serverPool;
	struct alias_link *aliaslink;

	buf = strdup (parms);
	if (!buf)
		errx (1, "redirect_port: strdup() failed");
/*
 * Extract local address.
 */
	ptr = strtok (buf, " \t");
	if (!ptr)
		errx (1, "redirect_address: missing local address");

	separator = strchr(ptr, ',');
	if (separator) {		/* LSNAT redirection syntax. */
		localAddr.s_addr = INADDR_NONE;
		serverPool = ptr;
	} else {
		StrToAddr (ptr, &localAddr);
		serverPool = NULL;
	}
/*
 * Extract public address.
 */
	ptr = strtok (NULL, " \t");
	if (!ptr)
		errx (1, "redirect_address: missing public address");

	StrToAddr (ptr, &publicAddr);
	aliaslink = LibAliasRedirectAddr(mla, localAddr, publicAddr);

/*
 * Setup LSNAT server pool.
 */
	if (serverPool != NULL && aliaslink != NULL) {
		ptr = strtok(serverPool, ",");
		while (ptr != NULL) {
			StrToAddr(ptr, &localAddr);
			LibAliasAddServer(mla, aliaslink, localAddr, htons(~0));
			ptr = strtok(NULL, ",");
		}
	}

	free (buf);
}