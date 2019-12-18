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
struct sockaddr {int /*<<< orphan*/  sa_len; } ;
struct netconfig {int dummy; } ;
struct netbuf {scalar_t__ buf; } ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int NI_MAXHOST ; 
 char* UNKNOWN ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getnameinfo (struct sockaddr*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char const*) ; 
 char* taddr2uaddr (struct netconfig*,struct netbuf*) ; 

__attribute__((used)) static bool_t
reply_proc(void *res, struct netbuf *who, struct netconfig *nconf)
	/* void *res;			Nothing comes back */
	/* struct netbuf *who;		Who sent us the reply */
	/* struct netconfig *nconf; 	On which transport the reply came */
{
	char *uaddr;
	char hostbuf[NI_MAXHOST];
	const char *hostname;
	struct sockaddr *sa = (struct sockaddr *)who->buf;

	if (getnameinfo(sa, sa->sa_len, hostbuf, NI_MAXHOST, NULL, 0, 0)) {
		hostname = UNKNOWN;
	} else {
		hostname = hostbuf;
	}
	uaddr = taddr2uaddr(nconf, who);
	if (uaddr == NULL) {
		printf("%s\t%s\n", UNKNOWN, hostname);
	} else {
		printf("%s\t%s\n", uaddr, hostname);
		free((char *)uaddr);
	}
	return (FALSE);
}