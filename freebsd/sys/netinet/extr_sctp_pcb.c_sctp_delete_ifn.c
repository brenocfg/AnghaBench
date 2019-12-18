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
struct sctp_ifn {int /*<<< orphan*/  registered_af; int /*<<< orphan*/  ifn_index; int /*<<< orphan*/  ifn_p; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct sctp_ifn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_DEREGISTER_INTERFACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_IPI_ADDR_WLOCK () ; 
 int /*<<< orphan*/  SCTP_IPI_ADDR_WUNLOCK () ; 
 int /*<<< orphan*/  next_bucket ; 
 int /*<<< orphan*/  next_ifn ; 
 struct sctp_ifn* sctp_find_ifn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_free_ifn (struct sctp_ifn*) ; 

__attribute__((used)) static void
sctp_delete_ifn(struct sctp_ifn *sctp_ifnp, int hold_addr_lock)
{
	struct sctp_ifn *found;

	found = sctp_find_ifn(sctp_ifnp->ifn_p, sctp_ifnp->ifn_index);
	if (found == NULL) {
		/* Not in the list.. sorry */
		return;
	}
	if (hold_addr_lock == 0)
		SCTP_IPI_ADDR_WLOCK();
	LIST_REMOVE(sctp_ifnp, next_bucket);
	LIST_REMOVE(sctp_ifnp, next_ifn);
	SCTP_DEREGISTER_INTERFACE(sctp_ifnp->ifn_index,
	    sctp_ifnp->registered_af);
	if (hold_addr_lock == 0)
		SCTP_IPI_ADDR_WUNLOCK();
	/* Take away the reference, and possibly free it */
	sctp_free_ifn(sctp_ifnp);
}