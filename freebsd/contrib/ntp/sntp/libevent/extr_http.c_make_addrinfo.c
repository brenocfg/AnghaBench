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
struct evutil_addrinfo {int ai_flags; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
typedef  int /*<<< orphan*/  strport ;
typedef  int /*<<< orphan*/  hints ;
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int EVUTIL_AI_ADDRCONFIG ; 
 int EVUTIL_AI_PASSIVE ; 
 int EVUTIL_EAI_SYSTEM ; 
 int NI_MAXSERV ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  event_warn (char*) ; 
 int /*<<< orphan*/  event_warnx (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evutil_gai_strerror (int) ; 
 int evutil_getaddrinfo (char const*,char*,struct evutil_addrinfo*,struct evutil_addrinfo**) ; 
 int /*<<< orphan*/  evutil_snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct evutil_addrinfo*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct evutil_addrinfo *
make_addrinfo(const char *address, ev_uint16_t port)
{
	struct evutil_addrinfo *ai = NULL;

	struct evutil_addrinfo hints;
	char strport[NI_MAXSERV];
	int ai_result;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	/* turn NULL hostname into INADDR_ANY, and skip looking up any address
	 * types we don't have an interface to connect to. */
	hints.ai_flags = EVUTIL_AI_PASSIVE|EVUTIL_AI_ADDRCONFIG;
	evutil_snprintf(strport, sizeof(strport), "%d", port);
	if ((ai_result = evutil_getaddrinfo(address, strport, &hints, &ai))
	    != 0) {
		if (ai_result == EVUTIL_EAI_SYSTEM)
			event_warn("getaddrinfo");
		else
			event_warnx("getaddrinfo: %s",
			    evutil_gai_strerror(ai_result));
		return (NULL);
	}

	return (ai);
}