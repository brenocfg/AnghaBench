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
typedef  void* uart_intr_func_t ;
struct uart_softc {int /*<<< orphan*/  mtx; void* intr_deassert; void* intr_assert; void* arg; } ;

/* Variables and functions */
 struct uart_softc* calloc (int,int) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_reset (struct uart_softc*) ; 

struct uart_softc *
uart_init(uart_intr_func_t intr_assert, uart_intr_func_t intr_deassert,
    void *arg)
{
	struct uart_softc *sc;

	sc = calloc(1, sizeof(struct uart_softc));

	sc->arg = arg;
	sc->intr_assert = intr_assert;
	sc->intr_deassert = intr_deassert;

	pthread_mutex_init(&sc->mtx, NULL);

	uart_reset(sc);

	return (sc);
}