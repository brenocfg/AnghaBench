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
struct tty {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_softc (struct tty*) ; 
 int /*<<< orphan*/  xencons_tx_flush (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
xencons_shutdown(void *arg, int howto)
{
	struct tty *tp;

	tp = arg;

	xencons_tx_flush(tty_softc(tp), 1);
}