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
typedef  int /*<<< orphan*/ * t_Handle ;
struct bman_softc {int dummy; } ;

/* Variables and functions */
 int BM_POOL_PutBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int EIO ; 
 int E_OK ; 
 int /*<<< orphan*/ * bman_portal_setup (struct bman_softc*) ; 
 struct bman_softc* bman_sc ; 
 int /*<<< orphan*/  sched_pin () ; 
 int /*<<< orphan*/  sched_unpin () ; 

int
bman_put_buffer(t_Handle pool, void *buffer)
{
	struct bman_softc *sc;
	t_Handle portal;
	int error;

	sc = bman_sc;
	sched_pin();

	portal = bman_portal_setup(sc);
	if (portal == NULL) {
		sched_unpin();
		return (EIO);
	}

	error = BM_POOL_PutBuf(pool, portal, buffer);

	sched_unpin();

	return ((error == E_OK) ? 0 : EIO);
}