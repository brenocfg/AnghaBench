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
struct socket {int dummy; } ;
struct ha_softc {int /*<<< orphan*/  ha_receiving; } ;

/* Variables and functions */
 int SU_OK ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ctl_ha_rupcall(struct socket *so, void *arg, int waitflag)
{
	struct ha_softc *softc = arg;

	wakeup(&softc->ha_receiving);
	return (SU_OK);
}