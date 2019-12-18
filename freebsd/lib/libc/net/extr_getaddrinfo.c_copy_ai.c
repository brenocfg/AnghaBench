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
typedef  struct sockaddr {int ai_addrlen; int /*<<< orphan*/ * ai_next; int /*<<< orphan*/ * ai_canonname; struct sockaddr const* ai_addr; } const sockaddr ;
typedef  struct addrinfo {int ai_addrlen; int /*<<< orphan*/ * ai_next; int /*<<< orphan*/ * ai_canonname; struct addrinfo const* ai_addr; } const addrinfo ;

/* Variables and functions */
 struct sockaddr const* calloc (int,size_t) ; 
 int /*<<< orphan*/  free (struct sockaddr const*) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr const*,struct sockaddr const*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct addrinfo *
copy_ai(const struct addrinfo *pai)
{
	struct addrinfo *ai;
	size_t l;

	l = sizeof(*ai) + pai->ai_addrlen;
	if ((ai = calloc(1, l)) == NULL)
		return NULL;
	memcpy(ai, pai, sizeof(*ai));
	ai->ai_addr = (struct sockaddr *)(void *)(ai + 1);
	memcpy(ai->ai_addr, pai->ai_addr, pai->ai_addrlen);

	if (pai->ai_canonname) {
		l = strlen(pai->ai_canonname) + 1;
		if ((ai->ai_canonname = malloc(l)) == NULL) {
			free(ai);
			return NULL;
		}
		strlcpy(ai->ai_canonname, pai->ai_canonname, l);
	} else {
		/* just to make sure */
		ai->ai_canonname = NULL;
	}

	ai->ai_next = NULL;

	return ai;
}