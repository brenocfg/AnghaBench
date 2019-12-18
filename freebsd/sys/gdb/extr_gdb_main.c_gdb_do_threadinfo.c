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
struct thread {int /*<<< orphan*/  td_tid; } ;
typedef  int /*<<< orphan*/  lwpid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  gdb_tx_begin (char) ; 
 int /*<<< orphan*/  gdb_tx_char (char) ; 
 int /*<<< orphan*/  gdb_tx_end () ; 
 int /*<<< orphan*/  gdb_tx_err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_tx_varhex (int /*<<< orphan*/ ) ; 
 scalar_t__ gdb_txbuf_has_capacity (size_t const) ; 
 struct thread* kdb_thr_next (struct thread*) ; 

__attribute__((used)) static void
gdb_do_threadinfo(struct thread **thr_iter)
{
	static struct thread * const done_sentinel = (void *)(uintptr_t)1;
	static const size_t tidsz_hex = sizeof(lwpid_t) * 2;
	size_t tds_sent;

	if (*thr_iter == NULL) {
		gdb_tx_err(ENXIO);
		return;
	}

	if (*thr_iter == done_sentinel) {
		gdb_tx_begin('l');
		*thr_iter = NULL;
		goto sendit;
	}

	gdb_tx_begin('m');

	for (tds_sent = 0;
	    *thr_iter != NULL && gdb_txbuf_has_capacity(tidsz_hex + 1);
	    *thr_iter = kdb_thr_next(*thr_iter), tds_sent++) {
		if (tds_sent > 0)
			gdb_tx_char(',');
		gdb_tx_varhex((*thr_iter)->td_tid);
	}

	/*
	 * Can't send EOF and "some" in same packet, so set a sentinel to send
	 * EOF when GDB asks us next.
	 */
	if (*thr_iter == NULL && tds_sent > 0)
		*thr_iter = done_sentinel;

sendit:
	gdb_tx_end();
}