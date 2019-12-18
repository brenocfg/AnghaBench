#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int lg_base; unsigned int ndelta; unsigned int lg_delta; } ;
typedef  TYPE_1__ sc_t ;
struct TYPE_5__ {TYPE_1__* sc; } ;
typedef  TYPE_2__ sc_data_t ;

/* Variables and functions */
 unsigned int SC_NBINS ; 
 int /*<<< orphan*/ * arena_binind_div_info ; 
 int /*<<< orphan*/  arena_dirty_decay_ms_default_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arena_muzzy_decay_ms_default_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  div_init (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  opt_dirty_decay_ms ; 
 int /*<<< orphan*/  opt_muzzy_decay_ms ; 

void
arena_boot(sc_data_t *sc_data) {
	arena_dirty_decay_ms_default_set(opt_dirty_decay_ms);
	arena_muzzy_decay_ms_default_set(opt_muzzy_decay_ms);
	for (unsigned i = 0; i < SC_NBINS; i++) {
		sc_t *sc = &sc_data->sc[i];
		div_init(&arena_binind_div_info[i],
		    (1U << sc->lg_base) + (sc->ndelta << sc->lg_delta));
	}
}