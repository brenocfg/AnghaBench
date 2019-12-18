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
struct session {int /*<<< orphan*/  s_mtx; int /*<<< orphan*/  s_sid; int /*<<< orphan*/ * s_ttyp; int /*<<< orphan*/  s_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SESSION ; 
 int /*<<< orphan*/  PROC_ID_SESSION ; 
 int /*<<< orphan*/  free (struct session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_id_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_rel_sess (int /*<<< orphan*/ *,struct session*) ; 

void
sess_release(struct session *s)
{

	if (refcount_release(&s->s_count)) {
		if (s->s_ttyp != NULL) {
			tty_lock(s->s_ttyp);
			tty_rel_sess(s->s_ttyp, s);
		}
		proc_id_clear(PROC_ID_SESSION, s->s_sid);
		mtx_destroy(&s->s_mtx);
		free(s, M_SESSION);
	}
}