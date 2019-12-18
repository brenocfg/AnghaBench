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
struct addrinfo {scalar_t__ ai_flags; scalar_t__ ai_family; scalar_t__ ai_socktype; scalar_t__ ai_protocol; scalar_t__ ai_addrlen; struct addrinfo* ai_next; int /*<<< orphan*/ * ai_canonname; int /*<<< orphan*/  ai_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
addrinfo_compare(struct addrinfo *ai0, struct addrinfo *ai1)
{
	struct addrinfo *at0, *at1;

	if (ai0 == NULL && ai1 == NULL)
		return (true);
	if (ai0 == NULL || ai1 == NULL)
		return (false);

	at0 = ai0;
	at1 = ai1;
	while (true) {
		if ((at0->ai_flags == at1->ai_flags) &&
		    (at0->ai_family == at1->ai_family) &&
		    (at0->ai_socktype == at1->ai_socktype) &&
		    (at0->ai_protocol == at1->ai_protocol) &&
		    (at0->ai_addrlen == at1->ai_addrlen) &&
		    (memcmp(at0->ai_addr, at1->ai_addr,
			at0->ai_addrlen) == 0)) {
			if (at0->ai_canonname != NULL &&
			    at1->ai_canonname != NULL) {
				if (strcmp(at0->ai_canonname,
				    at1->ai_canonname) != 0) {
					return (false);
				}
			}

			if (at0->ai_canonname == NULL &&
			    at1->ai_canonname != NULL) {
				return (false);
			}
			if (at0->ai_canonname != NULL &&
			    at1->ai_canonname == NULL) {
				return (false);
			}

			if (at0->ai_next == NULL && at1->ai_next == NULL)
				return (true);
			if (at0->ai_next == NULL || at1->ai_next == NULL)
				return (false);

			at0 = at0->ai_next;
			at1 = at1->ai_next;
		} else {
			return (false);
		}
	}

	/* NOTREACHED */
	fprintf(stderr, "Dead code reached in addrinfo_compare()\n");
	exit(1);
}