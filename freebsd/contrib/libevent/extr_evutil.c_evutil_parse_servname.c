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
struct servent {int /*<<< orphan*/  s_port; } ;
struct evutil_addrinfo {int ai_flags; } ;

/* Variables and functions */
 int EVUTIL_AI_NUMERICSERV ; 
 struct servent* getservbyname (char const*,char const*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int parse_numeric_servname (char const*) ; 

__attribute__((used)) static int
evutil_parse_servname(const char *servname, const char *protocol,
    const struct evutil_addrinfo *hints)
{
	int n = parse_numeric_servname(servname);
	if (n>=0)
		return n;
#if defined(EVENT__HAVE_GETSERVBYNAME) || defined(_WIN32)
	if (!(hints->ai_flags & EVUTIL_AI_NUMERICSERV)) {
		struct servent *ent = getservbyname(servname, protocol);
		if (ent) {
			return ntohs(ent->s_port);
		}
	}
#endif
	return -1;
}