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
struct mps_softc {int /*<<< orphan*/  ioc_pg8; } ;
typedef  int /*<<< orphan*/  Mpi2ConfigReply_t ;

/* Variables and functions */
 scalar_t__ mps_config_get_ioc_pg8 (struct mps_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
mps_base_static_config_pages(struct mps_softc *sc)
{
	Mpi2ConfigReply_t	mpi_reply;
	int			retry;

	retry = 0;
	while (mps_config_get_ioc_pg8(sc, &mpi_reply, &sc->ioc_pg8)) {
		retry++;
		if (retry > 5) {
			/* We need to Handle this situation */
			/*FIXME*/
			break;
		}
	}
}