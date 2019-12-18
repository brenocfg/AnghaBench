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
struct protoent {int p_proto; } ;
struct in_addr {void* s_addr; } ;

/* Variables and functions */
 void* INADDR_ANY ; 
 int /*<<< orphan*/  LibAliasRedirectProto (int /*<<< orphan*/ ,struct in_addr,struct in_addr,struct in_addr,int) ; 
 int /*<<< orphan*/  StrToAddr (char*,struct in_addr*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct protoent* getprotobyname (char*) ; 
 int /*<<< orphan*/  mla ; 
 char* strdup (char const*) ; 
 char* strtok (char*,char*) ; 

void
SetupProtoRedirect(const char* parms)
{
	char		*buf;
	char*		ptr;
	struct in_addr	localAddr;
	struct in_addr	publicAddr;
	struct in_addr	remoteAddr;
	int		proto;
	char*		protoName;
	struct protoent *protoent;

	buf = strdup (parms);
	if (!buf)
		errx (1, "redirect_port: strdup() failed");
/*
 * Extract protocol.
 */
	protoName = strtok(buf, " \t");
	if (!protoName)
		errx(1, "redirect_proto: missing protocol");

	protoent = getprotobyname(protoName);
	if (protoent == NULL)
		errx(1, "redirect_proto: unknown protocol %s", protoName);
	else
		proto = protoent->p_proto;
/*
 * Extract local address.
 */
	ptr = strtok(NULL, " \t");
	if (!ptr)
		errx(1, "redirect_proto: missing local address");
	else
		StrToAddr(ptr, &localAddr);
/*
 * Extract optional public address.
 */
	ptr = strtok(NULL, " \t");
	if (ptr)
		StrToAddr(ptr, &publicAddr);
	else
		publicAddr.s_addr = INADDR_ANY;
/*
 * Extract optional remote address.
 */
	ptr = strtok(NULL, " \t");
	if (ptr)
		StrToAddr(ptr, &remoteAddr);
	else
		remoteAddr.s_addr = INADDR_ANY;
/*
 * Create aliasing link.
 */
	(void)LibAliasRedirectProto(mla, localAddr, remoteAddr, publicAddr,
				       proto);

	free (buf);
}