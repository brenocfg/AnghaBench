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
struct time_regs {int dummy; } ;
struct nxprtc_softc {int /*<<< orphan*/  secaddr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WAITFLAGS ; 
 int iicdev_writeto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct time_regs*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
write_timeregs(struct nxprtc_softc *sc, struct time_regs *tregs)
{

	return (iicdev_writeto(sc->dev, sc->secaddr, tregs,
	    sizeof(*tregs), WAITFLAGS));
}