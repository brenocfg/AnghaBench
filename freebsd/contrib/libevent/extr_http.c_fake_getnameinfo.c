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
typedef  int /*<<< orphan*/  tmpserv ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int dummy; } ;
struct in_addr {int dummy; } ;
struct hostent {char* h_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int NI_NUMERICHOST ; 
 int /*<<< orphan*/  evutil_snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 struct hostent* gethostbyaddr (char*,int,int /*<<< orphan*/ ) ; 
 char* inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 size_t strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static int
fake_getnameinfo(const struct sockaddr *sa, size_t salen, char *host,
	size_t hostlen, char *serv, size_t servlen, int flags)
{
	struct sockaddr_in *sin = (struct sockaddr_in *)sa;

	if (serv != NULL) {
		char tmpserv[16];
		evutil_snprintf(tmpserv, sizeof(tmpserv),
		    "%d", ntohs(sin->sin_port));
		if (strlcpy(serv, tmpserv, servlen) >= servlen)
			return (-1);
	}

	if (host != NULL) {
		if (flags & NI_NUMERICHOST) {
			if (strlcpy(host, inet_ntoa(sin->sin_addr),
			    hostlen) >= hostlen)
				return (-1);
			else
				return (0);
		} else {
			struct hostent *hp;
			hp = gethostbyaddr((char *)&sin->sin_addr,
			    sizeof(struct in_addr), AF_INET);
			if (hp == NULL)
				return (-2);

			if (strlcpy(host, hp->h_name, hostlen) >= hostlen)
				return (-1);
			else
				return (0);
		}
	}
	return (0);
}