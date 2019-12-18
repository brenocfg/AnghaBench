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
struct TYPE_2__ {int /*<<< orphan*/  rfd; scalar_t__ opened; } ;
struct fifo {int size; } ;
struct uart_softc {int /*<<< orphan*/  mev; TYPE_1__ tty; struct fifo rxfifo; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  flushbuf ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bzero (struct fifo*,int) ; 
 int mevent_enable (int /*<<< orphan*/ ) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
rxfifo_reset(struct uart_softc *sc, int size)
{
	char flushbuf[32];
	struct fifo *fifo;
	ssize_t nread;
	int error;

	fifo = &sc->rxfifo;
	bzero(fifo, sizeof(struct fifo));
	fifo->size = size;

	if (sc->tty.opened) {
		/*
		 * Flush any unread input from the tty buffer.
		 */
		while (1) {
			nread = read(sc->tty.rfd, flushbuf, sizeof(flushbuf));
			if (nread != sizeof(flushbuf))
				break;
		}

		/*
		 * Enable mevent to trigger when new characters are available
		 * on the tty fd.
		 */
		error = mevent_enable(sc->mev);
		assert(error == 0);
	}
}