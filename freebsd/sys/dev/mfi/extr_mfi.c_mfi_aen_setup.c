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
struct TYPE_2__ {int /*<<< orphan*/  evt_class; int /*<<< orphan*/  locale; scalar_t__ reserved; } ;
union mfi_evt {int /*<<< orphan*/  word; TYPE_1__ members; } ;
typedef  scalar_t__ uint32_t ;
struct mfi_softc {int /*<<< orphan*/  mfi_boot_seq_num; int /*<<< orphan*/  mfi_io_lock; } ;
struct mfi_evt_log_state {scalar_t__ newest_seq_num; int /*<<< orphan*/  shutdown_seq_num; int /*<<< orphan*/  boot_seq_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_MFIBUF ; 
 int /*<<< orphan*/  free (struct mfi_evt_log_state*,int /*<<< orphan*/ ) ; 
 int mfi_aen_register (struct mfi_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfi_event_class ; 
 int /*<<< orphan*/  mfi_event_locale ; 
 int mfi_get_log_state (struct mfi_softc*,struct mfi_evt_log_state**) ; 
 int mfi_parse_entries (struct mfi_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
mfi_aen_setup(struct mfi_softc *sc, uint32_t seq_start)
{
	struct mfi_evt_log_state *log_state = NULL;
	union mfi_evt class_locale;
	int error = 0;
	uint32_t seq;

	mtx_assert(&sc->mfi_io_lock, MA_OWNED);

	class_locale.members.reserved = 0;
	class_locale.members.locale = mfi_event_locale;
	class_locale.members.evt_class  = mfi_event_class;

	if (seq_start == 0) {
		if ((error = mfi_get_log_state(sc, &log_state)) != 0)
			goto out;
		sc->mfi_boot_seq_num = log_state->boot_seq_num;

		/*
		 * Walk through any events that fired since the last
		 * shutdown.
		 */
		if ((error = mfi_parse_entries(sc, log_state->shutdown_seq_num,
		    log_state->newest_seq_num)) != 0)
			goto out;
		seq = log_state->newest_seq_num;
	} else
		seq = seq_start;
	error = mfi_aen_register(sc, seq, class_locale.word);
out:
	free(log_state, M_MFIBUF);

	return (error);
}