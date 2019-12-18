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
typedef  int /*<<< orphan*/  scr_stat ;
typedef  int /*<<< orphan*/  sc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 char* SC_DFLT_TERM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  init_scp (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_alloc_cut_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_alloc_history_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_alloc_scr_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_init_emulator (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static scr_stat
*alloc_scp(sc_softc_t *sc, int vty)
{
    scr_stat *scp;

    /* assert(sc_malloc) */

    scp = (scr_stat *)malloc(sizeof(scr_stat), M_DEVBUF, M_WAITOK);
    init_scp(sc, vty, scp);

    sc_alloc_scr_buffer(scp, TRUE, TRUE);
    if (sc_init_emulator(scp, SC_DFLT_TERM))
	sc_init_emulator(scp, "*");

#ifndef SC_NO_CUTPASTE
    sc_alloc_cut_buffer(scp, TRUE);
#endif

#ifndef SC_NO_HISTORY
    sc_alloc_history_buffer(scp, 0, 0, TRUE);
#endif

    return scp;
}