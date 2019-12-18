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
struct uart_phyp_softc {int node; int /*<<< orphan*/  sc_mtx; } ;
struct consdev {int /*<<< orphan*/  cn_pri; } ;
typedef  int /*<<< orphan*/  stdout ;
typedef  int phandle_t ;
typedef  scalar_t__ ihandle_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CN_DEAD ; 
 int /*<<< orphan*/  CN_NORMAL ; 
 int MTX_NOWITNESS ; 
 int MTX_QUIET ; 
 int MTX_SPIN ; 
 int OF_finddevice (char*) ; 
 int OF_getencprop (int,char*,scalar_t__*,int) ; 
 int OF_getprop (int,char*,char*,int) ; 
 int OF_instance_to_package (scalar_t__) ; 
 struct uart_phyp_softc* console_sc ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ uart_phyp_probe_node (struct uart_phyp_softc*) ; 

__attribute__((used)) static void
uart_phyp_cnprobe(struct consdev *cp)
{
	char buf[64];
	ihandle_t stdout;
	phandle_t input, chosen;
	static struct uart_phyp_softc sc;

	if ((chosen = OF_finddevice("/chosen")) == -1)
		goto fail;

	/* Check if OF has an active stdin/stdout */
	input = -1;
	if (OF_getencprop(chosen, "stdout", &stdout,
	    sizeof(stdout)) == sizeof(stdout) && stdout != 0)
		input = OF_instance_to_package(stdout);
	if (input == -1)
		goto fail;

	if (OF_getprop(input, "device_type", buf, sizeof(buf)) == -1)
		goto fail;
	if (strcmp(buf, "serial") != 0)
		goto fail;

	sc.node = input;
	if (uart_phyp_probe_node(&sc) != 0)
		goto fail;
	mtx_init(&sc.sc_mtx, "uart_phyp", NULL, MTX_SPIN | MTX_QUIET |
	    MTX_NOWITNESS);

	cp->cn_pri = CN_NORMAL;
	console_sc = &sc;
	return;
	
fail:
	cp->cn_pri = CN_DEAD;
	return;
}