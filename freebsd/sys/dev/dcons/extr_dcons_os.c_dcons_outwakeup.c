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
struct dcons_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcons_os_putc (struct dcons_softc*,char) ; 
 struct dcons_softc* tty_softc (struct tty*) ; 
 scalar_t__ ttydisc_getc (struct tty*,char*,int) ; 

__attribute__((used)) static void
dcons_outwakeup(struct tty *tp)
{
	struct dcons_softc *dc;
	char ch;

	dc = tty_softc(tp);

	while (ttydisc_getc(tp, &ch, sizeof ch) != 0)
		dcons_os_putc(dc, ch);
}