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
struct afd {size_t a_off; } ;
typedef  size_t socklen_t ;

/* Variables and functions */
 int EAI_MEMORY ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

__attribute__((used)) static int
getnameinfo_un(const struct afd *afd,
    const struct sockaddr *sa, socklen_t salen,
    char *host, size_t hostlen, char *serv, size_t servlen, int flags)
{
	size_t pathlen;

	if (serv != NULL && servlen > 0)
		*serv = '\0';
	if (host != NULL && hostlen > 0) {
		pathlen = salen - afd->a_off;

		if (pathlen + 1 > hostlen) {
			*host = '\0';
			return (EAI_MEMORY);
		}
		strlcpy(host, (const char *)sa + afd->a_off, pathlen + 1);
	}

	return (0);
}