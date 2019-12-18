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
typedef  int /*<<< orphan*/  trimmed ;
struct in_addr {int dummy; } ;
struct hostent {int /*<<< orphan*/ ** h_addr_list; int /*<<< orphan*/  h_name; } ;
typedef  int /*<<< orphan*/  lookup ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int HOSTNAME_FOUND ; 
 int HOSTNAME_INCORRECTNAME ; 
 int HOSTNAME_INVALIDADDR ; 
 int HOSTNAME_INVALIDNAME ; 
 int MAXHOSTNAMELEN ; 
 struct hostent* gethostbyaddr (char const*,int,int /*<<< orphan*/ ) ; 
 struct hostent* gethostbyname (char*) ; 
 char* inet_ntoa (struct in_addr const) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,struct in_addr const*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  trimdomain (char*,size_t) ; 

int
realhostname(char *host, size_t hsize, const struct in_addr *ip)
{
	char trimmed[MAXHOSTNAMELEN];
	int result;
	struct hostent *hp;

	result = HOSTNAME_INVALIDADDR;
	hp = gethostbyaddr((const char *)ip, sizeof(*ip), AF_INET);

	if (hp != NULL) {
		strlcpy(trimmed, hp->h_name, sizeof(trimmed));
		trimdomain(trimmed, strlen(trimmed));
		if (strlen(trimmed) <= hsize) {
			char lookup[MAXHOSTNAMELEN];

			strlcpy(lookup, hp->h_name, sizeof(lookup));
			hp = gethostbyname(lookup);
			if (hp == NULL)
				result = HOSTNAME_INVALIDNAME;
			else for (; ; hp->h_addr_list++) {
				if (*hp->h_addr_list == NULL) {
					result = HOSTNAME_INCORRECTNAME;
					break;
				}
				if (!memcmp(*hp->h_addr_list, ip, sizeof(*ip))) {
					strncpy(host, trimmed, hsize);
					return HOSTNAME_FOUND;
				}
			}
		}
	}

	strncpy(host, inet_ntoa(*ip), hsize);

	return result;
}