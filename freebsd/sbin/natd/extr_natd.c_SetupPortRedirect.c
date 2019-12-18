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
typedef  int u_short ;
struct in_addr {void* s_addr; } ;
struct alias_link {int dummy; } ;
typedef  int /*<<< orphan*/  port_range ;

/* Variables and functions */
 int GETLOPORT (int /*<<< orphan*/ ) ; 
 int GETNUMPORTS (int /*<<< orphan*/ ) ; 
 void* INADDR_ANY ; 
 void* INADDR_NONE ; 
 int /*<<< orphan*/  LibAliasAddServer (int /*<<< orphan*/ ,struct alias_link*,struct in_addr,int /*<<< orphan*/ ) ; 
 struct alias_link* LibAliasRedirectPort (int /*<<< orphan*/ ,struct in_addr,int /*<<< orphan*/ ,struct in_addr,int /*<<< orphan*/ ,struct in_addr,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SETLOPORT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETNUMPORTS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  StrToAddr (char*,struct in_addr*) ; 
 scalar_t__ StrToAddrAndPortRange (char*,struct in_addr*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ StrToPortRange (char*,char*,int /*<<< orphan*/ *) ; 
 int StrToProto (char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  mla ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 char* strtok (char*,char*) ; 

void SetupPortRedirect (const char* parms)
{
	char		*buf;
	char*		ptr;
	char*		serverPool;
	struct in_addr	localAddr;
	struct in_addr	publicAddr;
	struct in_addr	remoteAddr;
	port_range      portRange;
	u_short         localPort      = 0;
	u_short         publicPort     = 0;
	u_short         remotePort     = 0;
	u_short         numLocalPorts  = 0;
	u_short         numPublicPorts = 0;
	u_short         numRemotePorts = 0;
	int		proto;
	char*		protoName;
	char*		separator;
	int             i;
	struct alias_link *aliaslink = NULL;

	buf = strdup (parms);
	if (!buf)
		errx (1, "redirect_port: strdup() failed");
/*
 * Extract protocol.
 */
	protoName = strtok (buf, " \t");
	if (!protoName)
		errx (1, "redirect_port: missing protocol");

	proto = StrToProto (protoName);
/*
 * Extract local address.
 */
	ptr = strtok (NULL, " \t");
	if (!ptr)
		errx (1, "redirect_port: missing local address");

	separator = strchr(ptr, ',');
	if (separator) {		/* LSNAT redirection syntax. */
		localAddr.s_addr = INADDR_NONE;
		localPort = ~0;
		numLocalPorts = 1;
		serverPool = ptr;
	} else {
		if ( StrToAddrAndPortRange (ptr, &localAddr, protoName, &portRange) != 0 )
			errx (1, "redirect_port: invalid local port range");

		localPort     = GETLOPORT(portRange);
		numLocalPorts = GETNUMPORTS(portRange);
		serverPool = NULL;
	}

/*
 * Extract public port and optionally address.
 */
	ptr = strtok (NULL, " \t");
	if (!ptr)
		errx (1, "redirect_port: missing public port");

	separator = strchr (ptr, ':');
	if (separator) {
	        if (StrToAddrAndPortRange (ptr, &publicAddr, protoName, &portRange) != 0 )
		        errx (1, "redirect_port: invalid public port range");
	}
	else {
		publicAddr.s_addr = INADDR_ANY;
		if (StrToPortRange (ptr, protoName, &portRange) != 0)
		        errx (1, "redirect_port: invalid public port range");
	}

	publicPort     = GETLOPORT(portRange);
	numPublicPorts = GETNUMPORTS(portRange);

/*
 * Extract remote address and optionally port.
 */
	ptr = strtok (NULL, " \t");
	if (ptr) {
		separator = strchr (ptr, ':');
		if (separator) {
		        if (StrToAddrAndPortRange (ptr, &remoteAddr, protoName, &portRange) != 0)
			        errx (1, "redirect_port: invalid remote port range");
		} else {
		        SETLOPORT(portRange, 0);
			SETNUMPORTS(portRange, 1);
			StrToAddr (ptr, &remoteAddr);
		}
	}
	else {
	        SETLOPORT(portRange, 0);
		SETNUMPORTS(portRange, 1);
		remoteAddr.s_addr = INADDR_ANY;
	}

	remotePort     = GETLOPORT(portRange);
	numRemotePorts = GETNUMPORTS(portRange);

/*
 * Make sure port ranges match up, then add the redirect ports.
 */
	if (numLocalPorts != numPublicPorts)
	        errx (1, "redirect_port: port ranges must be equal in size");

	/* Remote port range is allowed to be '0' which means all ports. */
	if (numRemotePorts != numLocalPorts && (numRemotePorts != 1 || remotePort != 0))
	        errx (1, "redirect_port: remote port must be 0 or equal to local port range in size");

	for (i = 0 ; i < numPublicPorts ; ++i) {
	        /* If remotePort is all ports, set it to 0. */
	        u_short remotePortCopy = remotePort + i;
	        if (numRemotePorts == 1 && remotePort == 0)
		        remotePortCopy = 0;

		aliaslink = LibAliasRedirectPort (mla, localAddr,
						htons(localPort + i),
						remoteAddr,
						htons(remotePortCopy),
						publicAddr,
						htons(publicPort + i),
						proto);
	}

/*
 * Setup LSNAT server pool.
 */
	if (serverPool != NULL && aliaslink != NULL) {
		ptr = strtok(serverPool, ",");
		while (ptr != NULL) {
			if (StrToAddrAndPortRange(ptr, &localAddr, protoName, &portRange) != 0)
				errx(1, "redirect_port: invalid local port range");

			localPort = GETLOPORT(portRange);
			if (GETNUMPORTS(portRange) != 1)
				errx(1, "redirect_port: local port must be single in this context");
			LibAliasAddServer(mla, aliaslink, localAddr, htons(localPort));
			ptr = strtok(NULL, ",");
		}
	}
	
	free (buf);
}