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
struct ifnet {struct an_softc* if_softc; } ;
struct an_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLASH_DELAY (struct an_softc*,int) ; 
 int /*<<< orphan*/  an_init_locked (struct an_softc*) ; 

__attribute__((used)) static int
flashrestart(struct ifnet *ifp)
{
	int		status = 0;
	struct an_softc	*sc = ifp->if_softc;

	FLASH_DELAY(sc, 1024);		/* Added 12/7/00 */

	an_init_locked(sc);

	FLASH_DELAY(sc, 1024);		/* Added 12/7/00 */
	return status;
}