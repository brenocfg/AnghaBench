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
struct servent {int s_port; } ;
struct protoent {char* p_name; int p_proto; } ;
struct addrinfo {scalar_t__ ai_protocol; int ai_socktype; } ;

/* Variables and functions */
 int EAI_NONAME ; 
 int EAI_SOCKTYPE ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int SOCK_DGRAM ; 
 int SOCK_STREAM ; 
 struct protoent* getprotobynumber (scalar_t__) ; 
 struct servent* getservbyname (char const*,char const*) ; 
 int htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtol (char const*,char**,int) ; 

__attribute__((used)) static int
get_port_protocol_socktype (const char *servname,
			    const struct addrinfo *hints,
			    int *port,
			    int *protocol,
			    int *socktype)
{
    struct servent *se;
    const char *proto_str = NULL;

    *socktype = 0;

    if (hints != NULL && hints->ai_protocol != 0) {
	struct protoent *protoent = getprotobynumber (hints->ai_protocol);

	if (protoent == NULL)
	    return EAI_SOCKTYPE; /* XXX */

	proto_str = protoent->p_name;
	*protocol = protoent->p_proto;
    }

    if (hints != NULL)
	*socktype = hints->ai_socktype;

    if (*socktype == SOCK_STREAM) {
	se = getservbyname (servname, proto_str ? proto_str : "tcp");
	if (proto_str == NULL)
	    *protocol = IPPROTO_TCP;
    } else if (*socktype == SOCK_DGRAM) {
	se = getservbyname (servname, proto_str ? proto_str : "udp");
	if (proto_str == NULL)
	    *protocol = IPPROTO_UDP;
    } else if (*socktype == 0) {
	if (proto_str != NULL) {
	    se = getservbyname (servname, proto_str);
	} else {
	    se = getservbyname (servname, "tcp");
	    *protocol = IPPROTO_TCP;
	    *socktype = SOCK_STREAM;
	    if (se == NULL) {
		se = getservbyname (servname, "udp");
		*protocol = IPPROTO_UDP;
		*socktype = SOCK_DGRAM;
	    }
	}
    } else
	return EAI_SOCKTYPE;

    if (se == NULL) {
	char *endstr;

	*port = htons(strtol (servname, &endstr, 10));
	if (servname == endstr)
	    return EAI_NONAME;
    } else {
	*port = se->s_port;
    }
    return 0;
}