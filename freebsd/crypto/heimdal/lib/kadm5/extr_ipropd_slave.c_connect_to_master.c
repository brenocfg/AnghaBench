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
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  port ;
typedef  int /*<<< orphan*/  node ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int IPROP_PORT ; 
 int NI_MAXHOST ; 
 int NI_MAXSERV ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (char const*,char const*,struct addrinfo*,struct addrinfo**) ; 
 int getnameinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static int
connect_to_master (krb5_context context, const char *master,
		   const char *port_str)
{
    char port[NI_MAXSERV];
    struct addrinfo *ai, *a;
    struct addrinfo hints;
    int error;
    int s = -1;

    memset (&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;

    if (port_str == NULL) {
	snprintf(port, sizeof(port), "%u", IPROP_PORT);
	port_str = port;
    }

    error = getaddrinfo (master, port_str, &hints, &ai);
    if (error) {
	krb5_warnx(context, "Failed to get address of to %s: %s",
		   master, gai_strerror(error));
	return -1;
    }

    for (a = ai; a != NULL; a = a->ai_next) {
	char node[NI_MAXHOST];
	error = getnameinfo(a->ai_addr, a->ai_addrlen,
			    node, sizeof(node), NULL, 0, NI_NUMERICHOST);
	if (error)
	    strlcpy(node, "[unknown-addr]", sizeof(node));

	s = socket (a->ai_family, a->ai_socktype, a->ai_protocol);
	if (s < 0)
	    continue;
	if (connect (s, a->ai_addr, a->ai_addrlen) < 0) {
	    krb5_warn(context, errno, "connection failed to %s[%s]",
		      master, node);
	    close (s);
	    continue;
	}
	krb5_warnx(context, "connection successful "
		   "to master: %s[%s]", master, node);
	break;
    }
    freeaddrinfo (ai);

    if (a == NULL)
	return -1;

    return s;
}