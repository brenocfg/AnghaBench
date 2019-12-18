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
struct xencons_priv {int /*<<< orphan*/  callout; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XC_POLLTIME ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tty*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 struct xencons_priv* tty_softc (struct tty*) ; 
 int /*<<< orphan*/  xencons_timeout ; 
 int /*<<< orphan*/  xencons_tx (struct tty*) ; 

__attribute__((used)) static void
xencons_tty_outwakeup(struct tty *tp)
{
	struct xencons_priv *cons;

	cons = tty_softc(tp);

	callout_stop(&cons->callout);

	if (!xencons_tx(tp))
		callout_reset(&cons->callout, XC_POLLTIME,
		    xencons_timeout, tp);
}