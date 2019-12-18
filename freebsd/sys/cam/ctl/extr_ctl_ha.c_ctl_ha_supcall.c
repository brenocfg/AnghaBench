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
struct ha_softc {int dummy; } ;

/* Variables and functions */
 int SU_OK ; 
 int /*<<< orphan*/  ctl_ha_conn_wake (struct ha_softc*) ; 

__attribute__((used)) static int
ctl_ha_supcall(struct socket *so, void *arg, int waitflag)
{
	struct ha_softc *softc = arg;

	ctl_ha_conn_wake(softc);
	return (SU_OK);
}