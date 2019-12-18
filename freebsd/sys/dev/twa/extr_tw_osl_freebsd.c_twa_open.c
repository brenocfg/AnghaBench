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
struct twa_softc {int /*<<< orphan*/  open; } ;
struct thread {int dummy; } ;
struct cdev {scalar_t__ si_drv1; } ;
typedef  int /*<<< orphan*/  TW_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  TW_CL_TRUE ; 
 int /*<<< orphan*/  tw_osli_dbg_dprintf (int,struct twa_softc*,char*) ; 

__attribute__((used)) static TW_INT32
twa_open(struct cdev *dev, TW_INT32 flags, TW_INT32 fmt, struct thread *proc)
{
	struct twa_softc	*sc = (struct twa_softc *)(dev->si_drv1);

	tw_osli_dbg_dprintf(5, sc, "entered");
	sc->open = TW_CL_TRUE;
	return(0);
}