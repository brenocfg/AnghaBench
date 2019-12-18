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
struct iovec {int dummy; } ;
struct e82545_softc {int /*<<< orphan*/ * esc_be; } ;

/* Variables and functions */
 int /*<<< orphan*/  netbe_send (int /*<<< orphan*/ *,struct iovec*,int) ; 

__attribute__((used)) static void
e82545_transmit_backend(struct e82545_softc *sc, struct iovec *iov, int iovcnt)
{

	if (sc->esc_be == NULL)
		return;

	(void) netbe_send(sc->esc_be, iov, iovcnt);
}