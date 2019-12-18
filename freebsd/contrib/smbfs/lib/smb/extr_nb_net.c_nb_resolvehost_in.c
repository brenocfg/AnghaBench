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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_len; scalar_t__ sin_family; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct hostent {scalar_t__ h_addrtype; int h_length; int /*<<< orphan*/  h_addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int EAFNOSUPPORT ; 
 int ENETDOWN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 struct hostent* gethostbyname (char const*) ; 
 int /*<<< orphan*/  herror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htons (long) ; 
 struct sockaddr_in* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

int
nb_resolvehost_in(const char *name, struct sockaddr **dest, long smbtcpport)
{
	struct hostent* h;
	struct sockaddr_in *sinp;
	int len;

	h = gethostbyname(name);
	if (!h) {
		warnx("can't get server address `%s': ", name);
		herror(NULL);
		return ENETDOWN;
	}
	if (h->h_addrtype != AF_INET) {
		warnx("address for `%s' is not in the AF_INET family", name);
		return EAFNOSUPPORT;
	}
	if (h->h_length != 4) {
		warnx("address for `%s' has invalid length", name);
		return EAFNOSUPPORT;
	}
	len = sizeof(struct sockaddr_in);
	sinp = malloc(len);
	if (sinp == NULL)
		return ENOMEM;
	bzero(sinp, len);
	sinp->sin_len = len;
	sinp->sin_family = h->h_addrtype;
	memcpy(&sinp->sin_addr.s_addr, h->h_addr, 4);
	sinp->sin_port = htons(smbtcpport);
	*dest = (struct sockaddr*)sinp;
	return 0;
}