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
struct xencons_priv {int opened; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 struct xencons_priv* tty_softc (struct tty*) ; 

__attribute__((used)) static void
xencons_tty_close(struct tty *tp)
{
	struct xencons_priv *cons;

	cons = tty_softc(tp);

	cons->opened = false;
}