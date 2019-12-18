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
struct protoent {char const* p_name; } ;

/* Variables and functions */
#define  IPPROTO_SCTP 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 struct protoent* getprotobynumber (int) ; 

__attribute__((used)) static const char *
evutil_unparse_protoname(int proto)
{
	switch (proto) {
	case 0:
		return NULL;
	case IPPROTO_TCP:
		return "tcp";
	case IPPROTO_UDP:
		return "udp";
#ifdef IPPROTO_SCTP
	case IPPROTO_SCTP:
		return "sctp";
#endif
	default:
#ifdef EVENT__HAVE_GETPROTOBYNUMBER
		{
			struct protoent *ent = getprotobynumber(proto);
			if (ent)
				return ent->p_name;
		}
#endif
		return NULL;
	}
}