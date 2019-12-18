#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ nentries; int /*<<< orphan*/  idlist; } ;
typedef  int /*<<< orphan*/  SocketEntry ;
typedef  int /*<<< orphan*/  Identity ;

/* Variables and functions */
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_identity (int /*<<< orphan*/ *) ; 
 TYPE_1__* idtab ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  send_status (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
process_remove_all_identities(SocketEntry *e)
{
	Identity *id;

	/* Loop over all identities and clear the keys. */
	for (id = TAILQ_FIRST(&idtab->idlist); id;
	    id = TAILQ_FIRST(&idtab->idlist)) {
		TAILQ_REMOVE(&idtab->idlist, id, next);
		free_identity(id);
	}

	/* Mark that there are no identities. */
	idtab->nentries = 0;

	/* Send success. */
	send_status(e, 1);
}