#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty {int dummy; } ;
struct rp_port {TYPE_1__* rp_ctlp; int /*<<< orphan*/  rp_timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unbusy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rphardclose (struct tty*) ; 
 struct rp_port* tty_softc (struct tty*) ; 

__attribute__((used)) static void
rpclose(struct tty *tp)
{
	struct	rp_port	*rp;

	rp = tty_softc(tp);
	callout_stop(&rp->rp_timer);
	rphardclose(tp);
	device_unbusy(rp->rp_ctlp->dev);
}