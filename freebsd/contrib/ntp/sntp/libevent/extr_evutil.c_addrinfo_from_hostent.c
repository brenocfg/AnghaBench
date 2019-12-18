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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; void* sin6_port; int /*<<< orphan*/  sin6_family; int /*<<< orphan*/  sin_addr; void* sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr_in {int /*<<< orphan*/  sin6_addr; void* sin6_port; int /*<<< orphan*/  sin6_family; int /*<<< orphan*/  sin_addr; void* sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct hostent {scalar_t__ h_addrtype; int h_length; scalar_t__ h_name; scalar_t__* h_addr_list; } ;
struct evutil_addrinfo {int ai_flags; int /*<<< orphan*/ * ai_canonname; } ;
typedef  int /*<<< orphan*/  sin6 ;
typedef  int /*<<< orphan*/  sin ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int EVUTIL_AI_CANONNAME ; 
 scalar_t__ PF_INET ; 
 scalar_t__ PF_INET6 ; 
 int /*<<< orphan*/  event_warnx (char*) ; 
 struct evutil_addrinfo* evutil_addrinfo_append_ (struct evutil_addrinfo*,struct evutil_addrinfo*) ; 
 int /*<<< orphan*/  evutil_freeaddrinfo (struct evutil_addrinfo*) ; 
 struct evutil_addrinfo* evutil_new_addrinfo_ (struct sockaddr*,int,struct evutil_addrinfo const*) ; 
 void* htons (int) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * mm_strdup (scalar_t__) ; 

__attribute__((used)) static struct evutil_addrinfo *
addrinfo_from_hostent(const struct hostent *ent,
    int port, const struct evutil_addrinfo *hints)
{
	int i;
	struct sockaddr_in sin;
	struct sockaddr_in6 sin6;
	struct sockaddr *sa;
	int socklen;
	struct evutil_addrinfo *res=NULL, *ai;
	void *addrp;

	if (ent->h_addrtype == PF_INET) {
		memset(&sin, 0, sizeof(sin));
		sin.sin_family = AF_INET;
		sin.sin_port = htons(port);
		sa = (struct sockaddr *)&sin;
		socklen = sizeof(struct sockaddr_in);
		addrp = &sin.sin_addr;
		if (ent->h_length != sizeof(sin.sin_addr)) {
			event_warnx("Weird h_length from gethostbyname");
			return NULL;
		}
	} else if (ent->h_addrtype == PF_INET6) {
		memset(&sin6, 0, sizeof(sin6));
		sin6.sin6_family = AF_INET6;
		sin6.sin6_port = htons(port);
		sa = (struct sockaddr *)&sin6;
		socklen = sizeof(struct sockaddr_in);
		addrp = &sin6.sin6_addr;
		if (ent->h_length != sizeof(sin6.sin6_addr)) {
			event_warnx("Weird h_length from gethostbyname");
			return NULL;
		}
	} else
		return NULL;

	for (i = 0; ent->h_addr_list[i]; ++i) {
		memcpy(addrp, ent->h_addr_list[i], ent->h_length);
		ai = evutil_new_addrinfo_(sa, socklen, hints);
		if (!ai) {
			evutil_freeaddrinfo(res);
			return NULL;
		}
		res = evutil_addrinfo_append_(res, ai);
	}

	if (res && ((hints->ai_flags & EVUTIL_AI_CANONNAME) && ent->h_name)) {
		res->ai_canonname = mm_strdup(ent->h_name);
		if (res->ai_canonname == NULL) {
			evutil_freeaddrinfo(res);
			return NULL;
		}
	}

	return res;
}