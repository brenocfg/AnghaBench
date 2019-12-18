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
struct sockaddr {int dummy; } ;
struct client {int salen; int /*<<< orphan*/ * sock; int /*<<< orphan*/  servername; int /*<<< orphan*/  sa; int /*<<< orphan*/  moniker; } ;
typedef  int /*<<< orphan*/  hostname ;

/* Variables and functions */
 int MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 int /*<<< orphan*/  asprintf (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 struct client* ecalloc (int,int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  estrdup (char const*) ; 
 int /*<<< orphan*/  gethostname (char*,int) ; 
 int /*<<< orphan*/  getnameinfo (struct sockaddr*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpeername (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/ * krb5_storage_from_fd (int) ; 

__attribute__((used)) static struct client *
create_client(int fd, int port, const char *moniker)
{
    struct client *c;

    c = ecalloc(1, sizeof(*c));

    if (moniker) {
	c->moniker = estrdup(moniker);
    } else {
	char hostname[MAXHOSTNAMELEN];
	gethostname(hostname, sizeof(hostname));
	asprintf(&c->moniker, "gssmask: %s:%d", hostname, port);
    }

    {
	c->salen = sizeof(c->sa);
	getpeername(fd, (struct sockaddr *)&c->sa, &c->salen);

	getnameinfo((struct sockaddr *)&c->sa, c->salen,
		    c->servername, sizeof(c->servername),
		    NULL, 0, NI_NUMERICHOST);
    }

    c->sock = krb5_storage_from_fd(fd);
    if (c->sock == NULL)
	errx(1, "krb5_storage_from_fd");

    close(fd);

    return c;
}