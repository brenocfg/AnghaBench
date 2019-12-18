#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usock ;
struct sockaddr_un {unsigned int sun_len; int /*<<< orphan*/  sun_path; void* sun_family; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_4__ {TYPE_1__* first; } ;
struct config_file {int /*<<< orphan*/  control_port; scalar_t__ do_ip4; TYPE_2__ control_ifs; } ;
typedef  scalar_t__ socklen_t ;
struct TYPE_3__ {char* str; } ;

/* Variables and functions */
 void* AF_LOCAL ; 
 int ECONNREFUSED ; 
 int IPPROTO_TCP ; 
 int PF_INET ; 
 int PF_INET6 ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int WSAECONNREFUSED ; 
 int WSAGetLastError () ; 
 scalar_t__ addr_is_ip6 (struct sockaddr_storage*,scalar_t__) ; 
 scalar_t__ connect (int,struct sockaddr*,scalar_t__) ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  extstrtoaddr (char const*,struct sockaddr_storage*,scalar_t__*) ; 
 int /*<<< orphan*/  fatal_exit (char*,char const*) ; 
 int /*<<< orphan*/  ipstrtoaddr (char const*,int /*<<< orphan*/ ,struct sockaddr_storage*,scalar_t__*) ; 
 int /*<<< orphan*/  log_err (char*,char const*,char const*) ; 
 int /*<<< orphan*/  log_err_addr (char*,char const*,struct sockaddr_storage*,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int socket (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strchr (char const*,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char const* strerror (int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 char const* wsa_strerror (int) ; 

__attribute__((used)) static int
contact_server(const char* svr, struct config_file* cfg, int statuscmd)
{
	struct sockaddr_storage addr;
	socklen_t addrlen;
	int addrfamily = 0, proto = IPPROTO_TCP;
	int fd, useport = 1;
	/* use svr or the first config entry */
	if(!svr) {
		if(cfg->control_ifs.first) {
			svr = cfg->control_ifs.first->str;
		} else if(cfg->do_ip4) {
			svr = "127.0.0.1";
		} else {
			svr = "::1";
		}
		/* config 0 addr (everything), means ask localhost */
		if(strcmp(svr, "0.0.0.0") == 0)
			svr = "127.0.0.1";
		else if(strcmp(svr, "::0") == 0 ||
			strcmp(svr, "0::0") == 0 ||
			strcmp(svr, "0::") == 0 ||
			strcmp(svr, "::") == 0)
			svr = "::1";
	}
	if(strchr(svr, '@')) {
		if(!extstrtoaddr(svr, &addr, &addrlen))
			fatal_exit("could not parse IP@port: %s", svr);
#ifdef HAVE_SYS_UN_H
	} else if(svr[0] == '/') {
		struct sockaddr_un* usock = (struct sockaddr_un *) &addr;
		usock->sun_family = AF_LOCAL;
#ifdef HAVE_STRUCT_SOCKADDR_UN_SUN_LEN
		usock->sun_len = (unsigned)sizeof(usock);
#endif
		(void)strlcpy(usock->sun_path, svr, sizeof(usock->sun_path));
		addrlen = (socklen_t)sizeof(struct sockaddr_un);
		addrfamily = AF_LOCAL;
		useport = 0;
		proto = 0;
#endif
	} else {
		if(!ipstrtoaddr(svr, cfg->control_port, &addr, &addrlen))
			fatal_exit("could not parse IP: %s", svr);
	}

	if(addrfamily == 0)
		addrfamily = addr_is_ip6(&addr, addrlen)?PF_INET6:PF_INET;
	fd = socket(addrfamily, SOCK_STREAM, proto);
	if(fd == -1) {
#ifndef USE_WINSOCK
		fatal_exit("socket: %s", strerror(errno));
#else
		fatal_exit("socket: %s", wsa_strerror(WSAGetLastError()));
#endif
	}
	if(connect(fd, (struct sockaddr*)&addr, addrlen) < 0) {
#ifndef USE_WINSOCK
		int err = errno;
		if(!useport) log_err("connect: %s for %s", strerror(err), svr);
		else log_err_addr("connect", strerror(err), &addr, addrlen);
		if(err == ECONNREFUSED && statuscmd) {
			printf("unbound is stopped\n");
			exit(3);
		}
#else
		int wsaerr = WSAGetLastError();
		if(!useport) log_err("connect: %s for %s", wsa_strerror(wsaerr), svr);
		else log_err_addr("connect", wsa_strerror(wsaerr), &addr, addrlen);
		if(wsaerr == WSAECONNREFUSED && statuscmd) {
			printf("unbound is stopped\n");
			exit(3);
		}
#endif
		exit(1);
	}
	return fd;
}