#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct parport {scalar_t__ name; } ;
struct pardev_cb {void* private; int /*<<< orphan*/  wakeup; } ;
typedef  int /*<<< orphan*/  par_cb ;
struct TYPE_3__ {char* parname; int /*<<< orphan*/  port; int /*<<< orphan*/  device; int /*<<< orphan*/  parq; int /*<<< orphan*/  pardev; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct pardev_cb*,int /*<<< orphan*/ ,int) ; 
 struct parport* parport_find_base (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_put_port (struct parport*) ; 
 int /*<<< orphan*/  parport_register_dev_model (struct parport*,int /*<<< orphan*/ ,struct pardev_cb*,int) ; 
 int /*<<< orphan*/  pi_wake_up ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pi_register_parport(PIA *pi, int verbose, int unit)
{
	struct parport *port;
	struct pardev_cb par_cb;

	port = parport_find_base(pi->port);
	if (!port)
		return 0;
	memset(&par_cb, 0, sizeof(par_cb));
	par_cb.wakeup = pi_wake_up;
	par_cb.private = (void *)pi;
	pi->pardev = parport_register_dev_model(port, pi->device, &par_cb,
						unit);
	parport_put_port(port);
	if (!pi->pardev)
		return 0;

	init_waitqueue_head(&pi->parq);

	if (verbose)
		printk("%s: 0x%x is %s\n", pi->device, pi->port, port->name);

	pi->parname = (char *) port->name;

	return 1;
}