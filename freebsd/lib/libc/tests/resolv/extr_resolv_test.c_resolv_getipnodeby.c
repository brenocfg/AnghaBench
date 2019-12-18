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
struct hostent {char* h_name; int /*<<< orphan*/  h_addrtype; int /*<<< orphan*/  h_length; int /*<<< orphan*/  h_addr; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  freehostent (struct hostent*) ; 
 struct hostent* getipnodebyaddr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct hostent* getipnodebyname (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
resolv_getipnodeby(pthread_t self, char *host)
{
	char buf[1024];
	struct hostent *hp, *hp2;
	int len, h_error;

	hp = getipnodebyname(host, AF_INET, 0, &h_error);
	len = snprintf(buf, sizeof(buf), "%p: host %s %s\n",
	    self, host, (hp == NULL) ? "not found" : "ok");
	(void)write(STDOUT_FILENO, buf, len);
	if (hp) {
		memcpy(buf, hp->h_addr, hp->h_length);
		hp2 = getipnodebyaddr(buf, hp->h_length, hp->h_addrtype,
		    &h_error);
		if (hp2) {
			len = snprintf(buf, sizeof(buf),
			    "%p: reverse %s\n", self, hp2->h_name);
			(void)write(STDOUT_FILENO, buf, len);
		}
		if (hp2)
			freehostent(hp2);
	}
	if (hp)
		freehostent(hp);
	return hp ? 0 : -1;
}