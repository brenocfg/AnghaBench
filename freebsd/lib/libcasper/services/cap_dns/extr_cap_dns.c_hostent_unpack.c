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
struct hostent {int h_addrtype; int h_length; int /*<<< orphan*/ ** h_addr_list; int /*<<< orphan*/ ** h_aliases; int /*<<< orphan*/ * h_name; } ;
typedef  int /*<<< orphan*/  nvlname ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  NO_RECOVERY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 void* calloc (int,unsigned int) ; 
 int /*<<< orphan*/  h_errno ; 
 int /*<<< orphan*/  hostent_free (struct hostent*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  nvlist_get_binary (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  nvlist_get_string (int /*<<< orphan*/  const*,char*) ; 
 int snprintf (char*,int,char*,unsigned int) ; 
 void* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hostent *
hostent_unpack(const nvlist_t *nvl, struct hostent *hp)
{
	unsigned int ii, nitems;
	char nvlname[64];
	int n;

	hostent_free(hp);

	hp->h_name = strdup(nvlist_get_string(nvl, "name"));
	if (hp->h_name == NULL)
		goto fail;
	hp->h_addrtype = (int)nvlist_get_number(nvl, "addrtype");
	hp->h_length = (int)nvlist_get_number(nvl, "length");

	nitems = (unsigned int)nvlist_get_number(nvl, "naliases");
	hp->h_aliases = calloc(sizeof(hp->h_aliases[0]), nitems + 1);
	if (hp->h_aliases == NULL)
		goto fail;
	for (ii = 0; ii < nitems; ii++) {
		n = snprintf(nvlname, sizeof(nvlname), "alias%u", ii);
		assert(n > 0 && n < (int)sizeof(nvlname));
		hp->h_aliases[ii] =
		    strdup(nvlist_get_string(nvl, nvlname));
		if (hp->h_aliases[ii] == NULL)
			goto fail;
	}
	hp->h_aliases[ii] = NULL;

	nitems = (unsigned int)nvlist_get_number(nvl, "naddrs");
	hp->h_addr_list = calloc(sizeof(hp->h_addr_list[0]), nitems + 1);
	if (hp->h_addr_list == NULL)
		goto fail;
	for (ii = 0; ii < nitems; ii++) {
		hp->h_addr_list[ii] = malloc(hp->h_length);
		if (hp->h_addr_list[ii] == NULL)
			goto fail;
		n = snprintf(nvlname, sizeof(nvlname), "addr%u", ii);
		assert(n > 0 && n < (int)sizeof(nvlname));
		bcopy(nvlist_get_binary(nvl, nvlname, NULL),
		    hp->h_addr_list[ii], hp->h_length);
	}
	hp->h_addr_list[ii] = NULL;

	return (hp);
fail:
	hostent_free(hp);
	h_errno = NO_RECOVERY;
	return (NULL);
}