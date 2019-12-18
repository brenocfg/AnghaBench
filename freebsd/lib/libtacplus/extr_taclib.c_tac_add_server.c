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
struct TYPE_2__ {int sin_len; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_family; } ;
struct tac_server {int timeout; int flags; int /*<<< orphan*/ * secret; TYPE_1__ addr; } ;
struct tac_handle {size_t num_servers; struct tac_server* servers; } ;
struct hostent {int /*<<< orphan*/  h_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 size_t MAXSERVERS ; 
 int TACPLUS_PORT ; 
 int /*<<< orphan*/  generr (struct tac_handle*,char*,...) ; 
 struct hostent* gethostbyname (char const*) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  inet_aton (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * xstrdup (struct tac_handle*,char const*) ; 

int
tac_add_server(struct tac_handle *h, const char *host, int port,
    const char *secret, int timeout, int flags)
{
	struct tac_server *srvp;

	if (h->num_servers >= MAXSERVERS) {
		generr(h, "Too many TACACS+ servers specified");
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
	srvp->addr.sin_port = htons(port != 0 ? port : TACPLUS_PORT);
	if ((srvp->secret = xstrdup(h, secret)) == NULL)
		return -1;
	srvp->timeout = timeout;
	srvp->flags = flags;
	h->num_servers++;
	return 0;
}