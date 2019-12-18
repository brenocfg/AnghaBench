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
struct address_cache {int /*<<< orphan*/  ac_netid; int /*<<< orphan*/  ac_host; struct address_cache* ac_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 struct address_cache* front ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct address_cache *
check_cache(const char *host, const char *netid)
{
	struct address_cache *cptr;

	/* READ LOCK HELD ON ENTRY: rpcbaddr_cache_lock */

	for (cptr = front; cptr != NULL; cptr = cptr->ac_next) {
		if (!strcmp(cptr->ac_host, host) &&
		    !strcmp(cptr->ac_netid, netid)) {
#ifdef ND_DEBUG
			fprintf(stderr, "Found cache entry for %s: %s\n",
				host, netid);
#endif
			return (cptr);
		}
	}
	return ((struct address_cache *) NULL);
}