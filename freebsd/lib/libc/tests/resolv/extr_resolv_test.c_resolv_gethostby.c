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
 int /*<<< orphan*/  STDOUT_FILENO ; 
 struct hostent* gethostbyaddr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hostent* gethostbyname (char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
resolv_gethostby(pthread_t self, char *host)
{
	char buf[1024];
	struct hostent *hp, *hp2;
	int len;

	hp = gethostbyname(host);
	len = snprintf(buf, sizeof(buf), "%p: host %s %s\n",
	    self, host, (hp == NULL) ? "not found" : "ok");
	(void)write(STDOUT_FILENO, buf, len);
	if (hp) {
		memcpy(buf, hp->h_addr, hp->h_length);
		hp2 = gethostbyaddr(buf, hp->h_length, hp->h_addrtype);
		if (hp2) {
			len = snprintf(buf, sizeof(buf),
			    "%p: reverse %s\n", self, hp2->h_name);
			(void)write(STDOUT_FILENO, buf, len);
		}
	}
	return hp ? 0 : -1;
}