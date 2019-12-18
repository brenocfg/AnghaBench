#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct in_addr {int dummy; } ;
struct hostent_data {char* hostbuf; char** h_addr_ptrs; scalar_t__ host_addr; int /*<<< orphan*/ ** host_aliases; } ;
struct hostent {int h_addrtype; char* h_name; char** h_addr_list; int /*<<< orphan*/ ** h_aliases; int /*<<< orphan*/  h_length; } ;
typedef  TYPE_1__* res_state ;
struct TYPE_4__ {unsigned int options; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  HOST_NOT_FOUND ; 
 size_t MAXDNAME ; 
 int /*<<< orphan*/  NETDB_INTERNAL ; 
 int /*<<< orphan*/  NETDB_SUCCESS ; 
 int /*<<< orphan*/  NS_IN6ADDRSZ ; 
 int /*<<< orphan*/  NS_INADDRSZ ; 
 int /*<<< orphan*/  RES_SET_H_ERRNO (TYPE_1__*,int /*<<< orphan*/ ) ; 
 unsigned int RES_USE_INET6 ; 
 scalar_t__ __copy_hostent (struct hostent*,struct hostent*,char*,size_t) ; 
 struct hostent_data* __hostent_data_init () ; 
 int /*<<< orphan*/  _map_v4v6_address (char*,char*) ; 
 int /*<<< orphan*/  errno ; 
 int inet_aton (char const*,struct in_addr*) ; 
 int inet_pton (int,char const*,scalar_t__) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

__attribute__((used)) static int
fakeaddr(const char *name, int af, struct hostent *hp, char *buf,
    size_t buflen, res_state statp)
{
	struct hostent_data *hed;
	struct hostent he;

	if ((hed = __hostent_data_init()) == NULL) {
		errno = ENOMEM;
		RES_SET_H_ERRNO(statp, NETDB_INTERNAL);
		return (-1);
	}

	if ((af != AF_INET ||
	    inet_aton(name, (struct in_addr *)hed->host_addr) != 1) &&
	    inet_pton(af, name, hed->host_addr) != 1) {
		RES_SET_H_ERRNO(statp, HOST_NOT_FOUND);
		return (-1);
	}
	strncpy(hed->hostbuf, name, MAXDNAME);
	hed->hostbuf[MAXDNAME] = '\0';
	if (af == AF_INET && (statp->options & RES_USE_INET6) != 0U) {
		_map_v4v6_address((char *)hed->host_addr,
		    (char *)hed->host_addr);
		af = AF_INET6;
	}
	he.h_addrtype = af;
	switch(af) {
	case AF_INET:
		he.h_length = NS_INADDRSZ;
		break;
	case AF_INET6:
		he.h_length = NS_IN6ADDRSZ;
		break;
	default:
		errno = EAFNOSUPPORT;
		RES_SET_H_ERRNO(statp, NETDB_INTERNAL);
		return (-1);
	}
	he.h_name = hed->hostbuf;
	he.h_aliases = hed->host_aliases;
	hed->host_aliases[0] = NULL;
	hed->h_addr_ptrs[0] = (char *)hed->host_addr;
	hed->h_addr_ptrs[1] = NULL;
	he.h_addr_list = hed->h_addr_ptrs;
	if (__copy_hostent(&he, hp, buf, buflen) != 0) {
		RES_SET_H_ERRNO(statp, NETDB_INTERNAL);
		return (-1);
	}
	RES_SET_H_ERRNO(statp, NETDB_SUCCESS);
	return (0);
}