#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {void* sa_family; } ;
struct addrinfo {int ai_family; int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; TYPE_1__ sa; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_flags; } ;
typedef  struct addrinfo sockunion_t ;

/* Variables and functions */
 void* AF_UNSPEC ; 
 int /*<<< orphan*/  AI_NUMERICHOST ; 
 int /*<<< orphan*/  EINVAL ; 
 int PF_UNSPEC ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char const*,char*,struct addrinfo*,struct addrinfo**) ; 
 scalar_t__ if_nametoindex (char const*) ; 
 int /*<<< orphan*/  memcpy (struct addrinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
parse_cmd_args(sockunion_t *psu, sockunion_t *psu2,
    const char *str1, const char *str2, const char *str3)
{
	struct addrinfo		 hints;
	struct addrinfo		*res;
	uint32_t		 ifindex;
	int			 af, error;

	assert(psu != NULL);
	assert(str1 != NULL);
	assert(str2 != NULL);

	af = AF_UNSPEC;

	ifindex = if_nametoindex(str2);
	if (ifindex == 0)
		return (0);

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = AI_NUMERICHOST;
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	memset(psu, 0, sizeof(sockunion_t));
	psu->sa.sa_family = AF_UNSPEC;

	error = getaddrinfo(str1, "0", &hints, &res);
	if (error) {
		warnx("getaddrinfo: %s", gai_strerror(error));
		return (0);
	}
	assert(res != NULL);
	af = res->ai_family;
	memcpy(psu, res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);

	/* sscanf() may pass the empty string. */
	if (psu2 != NULL && str3 != NULL && *str3 != '\0') {
		memset(psu2, 0, sizeof(sockunion_t));
		psu2->sa.sa_family = AF_UNSPEC;

		/* look for following address family; str3 is *optional*. */
		hints.ai_family = af;
		error = getaddrinfo(str3, "0", &hints, &res);
		if (error) {
			warnx("getaddrinfo: %s", gai_strerror(error));
			ifindex = 0;
		} else {
			if (af != res->ai_family) {
				errno = EINVAL; /* XXX */
				ifindex = 0;
			}
			memcpy(psu2, res->ai_addr, res->ai_addrlen);
			freeaddrinfo(res);
		}
	}

	return (ifindex);
}