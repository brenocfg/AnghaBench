#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ubt_softc_p ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/ * hook_p ;
struct TYPE_6__ {int /*<<< orphan*/ * sc_hook; } ;

/* Variables and functions */
 int ENETDOWN ; 
 int /*<<< orphan*/  NG_FREE_M (struct mbuf*) ; 
 int /*<<< orphan*/  NG_HOOK_REF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_HOOK_UNREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_SEND_DATA_ONLY (int,int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  UBT_NG_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  UBT_NG_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  UBT_STAT_IERROR (TYPE_1__*) ; 

__attribute__((used)) static int
ubt_fwd_mbuf_up(ubt_softc_p sc, struct mbuf **m)
{
	hook_p	hook;
	int	error;

	/*
	 * Close the race with Netgraph hook newhook/disconnect methods.
	 * Save the hook pointer atomically. Two cases are possible:
	 *
	 * 1) The hook pointer is NULL. It means disconnect method got
	 *    there first. In this case we are done.
	 *
	 * 2) The hook pointer is not NULL. It means that hook pointer
	 *    could be either in valid or invalid (i.e. in the process
	 *    of disconnect) state. In any case grab an extra reference
	 *    to protect the hook pointer.
	 *
	 * It is ok to pass hook in invalid state to NG_SEND_DATA_ONLY() as
	 * it checks for it. Drop extra reference after NG_SEND_DATA_ONLY().
	 */

	UBT_NG_LOCK(sc);
	if ((hook = sc->sc_hook) != NULL)
		NG_HOOK_REF(hook);
	UBT_NG_UNLOCK(sc);

	if (hook == NULL) {
		NG_FREE_M(*m);
		return (ENETDOWN);
	}

	NG_SEND_DATA_ONLY(error, hook, *m);
	NG_HOOK_UNREF(hook);

	if (error != 0)
		UBT_STAT_IERROR(sc);

	return (error);
}