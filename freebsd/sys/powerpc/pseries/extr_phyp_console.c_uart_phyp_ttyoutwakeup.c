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
struct uart_phyp_softc {int dummy; } ;
struct tty {int dummy; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 struct uart_phyp_softc* tty_softc (struct tty*) ; 
 int ttydisc_getc (struct tty*,char*,int) ; 
 int /*<<< orphan*/  uart_phyp_put (struct uart_phyp_softc*,char*,int) ; 

__attribute__((used)) static void
uart_phyp_ttyoutwakeup(struct tty *tp)
{
	struct uart_phyp_softc *sc;
	char buffer[8];
	int len;

	sc = tty_softc(tp);
	
	while ((len = ttydisc_getc(tp, buffer, sizeof(buffer))) != 0)
		uart_phyp_put(sc, buffer, len);
}