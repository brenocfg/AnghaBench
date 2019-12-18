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
struct addrinfo {int ai_flags; int ai_family; int ai_socktype; int ai_protocol; int /*<<< orphan*/ * ai_next; void* ai_addr; int /*<<< orphan*/ * ai_canonname; scalar_t__ ai_addrlen; } ;
typedef  scalar_t__ socklen_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (void const*,void*,size_t) ; 
 char* dnvlist_get_string (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct addrinfo*) ; 
 struct addrinfo* malloc (int) ; 
 void* nvlist_get_binary (int /*<<< orphan*/  const*,char*,size_t*) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static struct addrinfo *
addrinfo_unpack(const nvlist_t *nvl)
{
	struct addrinfo *ai;
	const void *addr;
	size_t addrlen;
	const char *canonname;

	addr = nvlist_get_binary(nvl, "ai_addr", &addrlen);
	ai = malloc(sizeof(*ai) + addrlen);
	if (ai == NULL)
		return (NULL);
	ai->ai_flags = (int)nvlist_get_number(nvl, "ai_flags");
	ai->ai_family = (int)nvlist_get_number(nvl, "ai_family");
	ai->ai_socktype = (int)nvlist_get_number(nvl, "ai_socktype");
	ai->ai_protocol = (int)nvlist_get_number(nvl, "ai_protocol");
	ai->ai_addrlen = (socklen_t)addrlen;
	canonname = dnvlist_get_string(nvl, "ai_canonname", NULL);
	if (canonname != NULL) {
		ai->ai_canonname = strdup(canonname);
		if (ai->ai_canonname == NULL) {
			free(ai);
			return (NULL);
		}
	} else {
		ai->ai_canonname = NULL;
	}
	ai->ai_addr = (void *)(ai + 1);
	bcopy(addr, ai->ai_addr, addrlen);
	ai->ai_next = NULL;

	return (ai);
}