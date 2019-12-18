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
struct hostent {char** h_addr_list; int /*<<< orphan*/  h_addrtype; int /*<<< orphan*/  h_length; } ;
struct addrinfo {int dummy; } ;

/* Variables and functions */
 int AI_CANONNAME ; 
 int EAI_MEMORY ; 
 int add_one (int,int,int,struct addrinfo***,int (*) (struct addrinfo*,void*,int),char*,char*) ; 
 int /*<<< orphan*/  freehostent (struct hostent*) ; 
 struct hostent* getipnodebyaddr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 char* hostent_find_fqdn (struct hostent*) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int
add_hostent (int port, int protocol, int socktype,
	     struct addrinfo ***current,
	     int (*func)(struct addrinfo *, void *data, int port),
	     struct hostent *he, int *flags)
{
    int ret;
    char *canonname = NULL;
    char **h;

    if (*flags & AI_CANONNAME) {
	struct hostent *he2 = NULL;
	const char *tmp_canon;

	tmp_canon = hostent_find_fqdn (he);
	if (strchr (tmp_canon, '.') == NULL) {
	    int error;

	    he2 = getipnodebyaddr (he->h_addr_list[0], he->h_length,
				   he->h_addrtype, &error);
	    if (he2 != NULL) {
		const char *tmp = hostent_find_fqdn (he2);

		if (strchr (tmp, '.') != NULL)
		    tmp_canon = tmp;
	    }
	}

	canonname = strdup (tmp_canon);
	if (he2 != NULL)
	    freehostent (he2);
	if (canonname == NULL)
	    return EAI_MEMORY;
    }

    for (h = he->h_addr_list; *h != NULL; ++h) {
	ret = add_one (port, protocol, socktype,
		       current, func, *h, canonname);
	if (ret)
	    return ret;
	if (*flags & AI_CANONNAME) {
	    *flags &= ~AI_CANONNAME;
	    canonname = NULL;
	}
    }
    return 0;
}