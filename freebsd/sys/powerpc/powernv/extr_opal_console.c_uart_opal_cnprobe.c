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
struct uart_opal_softc {int node; int /*<<< orphan*/  sc_mtx; } ;
struct consdev {int /*<<< orphan*/  cn_pri; struct uart_opal_softc* cn_arg; } ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CN_DEAD ; 
 int /*<<< orphan*/  CN_NORMAL ; 
 int MTX_NOWITNESS ; 
 int MTX_QUIET ; 
 int MTX_SPIN ; 
 int OF_finddevice (char*) ; 
 scalar_t__ OF_getprop (int,char*,char*,int) ; 
 struct uart_opal_softc* console_sc ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ opal_check () ; 
 struct consdev* stdout_cp ; 
 scalar_t__ uart_opal_probe_node (struct uart_opal_softc*) ; 

__attribute__((used)) static void
uart_opal_cnprobe(struct consdev *cp)
{
	char buf[64];
	phandle_t input, chosen;
	static struct uart_opal_softc sc;

	if (opal_check() != 0)
		goto fail;

	if ((chosen = OF_finddevice("/chosen")) == -1)
		goto fail;

	/* Check if OF has an active stdin/stdout */
	if (OF_getprop(chosen, "linux,stdout-path", buf, sizeof(buf)) <= 0)
		goto fail;
	
	input = OF_finddevice(buf);
	if (input == -1)
		goto fail;

	sc.node = input;
	if (uart_opal_probe_node(&sc) != 0)
		goto fail;
	mtx_init(&sc.sc_mtx, "uart_opal", NULL, MTX_SPIN | MTX_QUIET |
	    MTX_NOWITNESS);

	cp->cn_pri = CN_NORMAL;
	console_sc = &sc;
	cp->cn_arg = console_sc;
	stdout_cp = cp;
	return;
	
fail:
	cp->cn_pri = CN_DEAD;
	return;
}