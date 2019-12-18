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
struct its_cmd {int dummy; } ;
struct gicv3_its_softc {int sc_its_cmd_next_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GITS_CREADR ; 
 int ITS_CMDQ_SIZE ; 
 int gic_its_read_4 (struct gicv3_its_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
its_cmd_queue_full(struct gicv3_its_softc *sc)
{
	size_t read_idx, next_write_idx;

	/* Get the index of the next command */
	next_write_idx = (sc->sc_its_cmd_next_idx + 1) %
	    (ITS_CMDQ_SIZE / sizeof(struct its_cmd));
	/* And the index of the current command being read */
	read_idx = gic_its_read_4(sc, GITS_CREADR) / sizeof(struct its_cmd);

	/*
	 * The queue is full when the write offset points
	 * at the command before the current read offset.
	 */
	return (next_write_idx == read_idx);
}