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
struct netbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct address_cache {struct address_cache* ac_next; struct address_cache* ac_uaddr; struct address_cache* ac_taddr; struct address_cache* buf; struct address_cache* ac_netid; struct address_cache* ac_host; } ;

/* Variables and functions */
 int /*<<< orphan*/  cachesize ; 
 int /*<<< orphan*/  free (struct address_cache*) ; 
 struct address_cache* front ; 
 int /*<<< orphan*/  memcmp (struct address_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
delete_cache(struct netbuf *addr)
{
	struct address_cache *cptr, *prevptr = NULL;

	/* WRITE LOCK HELD ON ENTRY: rpcbaddr_cache_lock */
	for (cptr = front; cptr != NULL; cptr = cptr->ac_next) {
		if (!memcmp(cptr->ac_taddr->buf, addr->buf, addr->len)) {
			free(cptr->ac_host);
			free(cptr->ac_netid);
			free(cptr->ac_taddr->buf);
			free(cptr->ac_taddr);
			free(cptr->ac_uaddr);
			if (prevptr)
				prevptr->ac_next = cptr->ac_next;
			else
				front = cptr->ac_next;
			free(cptr);
			cachesize--;
			break;
		}
		prevptr = cptr;
	}
}