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
typedef  int /*<<< orphan*/  u_short ;
struct servent {void* s_port; } ;
struct TYPE_2__ {int sin_len; void* sin_port; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_family; } ;
struct rad_server {int timeout; int max_tries; int dead_time; int /*<<< orphan*/  bindto; scalar_t__ next_probe; scalar_t__ is_dead; scalar_t__ num_tries; int /*<<< orphan*/ * secret; TYPE_1__ addr; } ;
struct rad_handle {size_t num_servers; scalar_t__ type; struct rad_server* servers; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct hostent {int /*<<< orphan*/  h_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 size_t MAXSERVERS ; 
 int /*<<< orphan*/  RADACCT_PORT ; 
 scalar_t__ RADIUS_AUTH ; 
 int /*<<< orphan*/  RADIUS_PORT ; 
 int /*<<< orphan*/  generr (struct rad_handle*,char*,...) ; 
 struct hostent* gethostbyname (char const*) ; 
 struct servent* getservbyname (char*,char*) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_aton (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

int
rad_add_server_ex(struct rad_handle *h, const char *host, int port,
    const char *secret, int timeout, int tries, int dead_time,
    struct in_addr *bindto)
{
	struct rad_server *srvp;

	if (h->num_servers >= MAXSERVERS) {
		generr(h, "Too many RADIUS servers specified");
		return -1;
	}
	srvp = &h->servers[h->num_servers];

	memset(&srvp->addr, 0, sizeof srvp->addr);
	srvp->addr.sin_len = sizeof srvp->addr;
	srvp->addr.sin_family = AF_INET;
	if (!inet_aton(host, &srvp->addr.sin_addr)) {
		struct hostent *hent;

		if ((hent = gethostbyname(host)) == NULL) {
			generr(h, "%s: host not found", host);
			return -1;
		}
		memcpy(&srvp->addr.sin_addr, hent->h_addr,
		    sizeof srvp->addr.sin_addr);
	}
	if (port != 0)
		srvp->addr.sin_port = htons((u_short)port);
	else {
		struct servent *sent;

		if (h->type == RADIUS_AUTH)
			srvp->addr.sin_port =
			    (sent = getservbyname("radius", "udp")) != NULL ?
				sent->s_port : htons(RADIUS_PORT);
		else
			srvp->addr.sin_port =
			    (sent = getservbyname("radacct", "udp")) != NULL ?
				sent->s_port : htons(RADACCT_PORT);
	}
	if ((srvp->secret = strdup(secret)) == NULL) {
		generr(h, "Out of memory");
		return -1;
	}
	srvp->timeout = timeout;
	srvp->max_tries = tries;
	srvp->num_tries = 0;
	srvp->is_dead = 0;
	srvp->dead_time = dead_time;
	srvp->next_probe = 0;
	srvp->bindto = bindto->s_addr;
	h->num_servers++;
	return 0;
}