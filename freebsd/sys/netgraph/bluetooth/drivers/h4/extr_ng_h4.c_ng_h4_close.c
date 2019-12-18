#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty {int /*<<< orphan*/ * t_lsc; int /*<<< orphan*/  t_outq; } ;
typedef  TYPE_1__* ng_h4_info_p ;
struct TYPE_4__ {int dying; int /*<<< orphan*/  node; int /*<<< orphan*/  timo; } ;

/* Variables and functions */
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  NG_H4_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  NG_H4_UNLOCK (TYPE_1__*) ; 
 scalar_t__ callout_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clist_free_cblocks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_uncallout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttyflush (struct tty*,int) ; 

__attribute__((used)) static int
ng_h4_close(struct tty *tp, int flag)
{
	ng_h4_info_p	sc = (ng_h4_info_p) tp->t_lsc;

	ttyflush(tp, FREAD | FWRITE);
	clist_free_cblocks(&tp->t_outq);

	if (sc != NULL) {
		NG_H4_LOCK(sc);

		if (callout_pending(&sc->timo))
			ng_uncallout(&sc->timo, sc->node);

		tp->t_lsc = NULL;
		sc->dying = 1;

		NG_H4_UNLOCK(sc);

		ng_rmnode_self(sc->node);
	}

	return (0);
}