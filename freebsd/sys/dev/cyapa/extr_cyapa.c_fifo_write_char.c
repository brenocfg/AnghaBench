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
typedef  int /*<<< orphan*/  uint8_t ;
struct cyapa_softc {int dummy; } ;
struct cyapa_fifo {size_t windex; scalar_t__ rindex; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 size_t CYAPA_BUFMASK ; 
 scalar_t__ CYAPA_BUFSIZE ; 
 int /*<<< orphan*/  CYAPA_LOCK_ASSERT (struct cyapa_softc*) ; 

__attribute__((used)) static void
fifo_write_char(struct cyapa_softc *sc, struct cyapa_fifo *fifo, uint8_t c)
{

	CYAPA_LOCK_ASSERT(sc);

	if (fifo->windex - fifo->rindex < CYAPA_BUFSIZE) {
		fifo->buf[fifo->windex & CYAPA_BUFMASK] = c;
		++fifo->windex;
	}
}