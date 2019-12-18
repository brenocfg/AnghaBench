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
struct dtsec_softc {int /*<<< orphan*/ * sc_fi_zone; int /*<<< orphan*/  sc_fi_zname; int /*<<< orphan*/  sc_dev; } ;
struct dtsec_rm_frame_info {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/ * uma_zcreate (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
dtsec_rm_fi_pool_init(struct dtsec_softc *sc)
{

	snprintf(sc->sc_fi_zname, sizeof(sc->sc_fi_zname), "%s: Frame Info",
	    device_get_nameunit(sc->sc_dev));

	sc->sc_fi_zone = uma_zcreate(sc->sc_fi_zname,
	    sizeof(struct dtsec_rm_frame_info), NULL, NULL, NULL, NULL,
	    UMA_ALIGN_PTR, 0);
	if (sc->sc_fi_zone == NULL)
		return (EIO);

	return (0);
}