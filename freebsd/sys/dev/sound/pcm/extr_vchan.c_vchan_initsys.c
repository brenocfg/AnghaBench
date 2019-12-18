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
struct snddev_info {int /*<<< orphan*/  rec_sysctl_tree; int /*<<< orphan*/  rec_sysctl_ctx; int /*<<< orphan*/  play_sysctl_tree; int /*<<< orphan*/  play_sysctl_ctx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CTLFLAG_RWTUN ; 
 int CTLTYPE_INT ; 
 int CTLTYPE_STRING ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  PLAY ; 
 int /*<<< orphan*/  REC ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCHAN_SYSCTL_DATA (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCHAN_SYSCTL_DATA_SIZE ; 
 struct snddev_info* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_dev_pcm_vchanformat ; 
 int /*<<< orphan*/  sysctl_dev_pcm_vchanmode ; 
 int /*<<< orphan*/  sysctl_dev_pcm_vchanrate ; 
 int /*<<< orphan*/  sysctl_dev_pcm_vchans ; 

void
vchan_initsys(device_t dev)
{
	struct snddev_info *d;
	int unit;

	unit = device_get_unit(dev);
	d = device_get_softc(dev);

	/* Play */
	SYSCTL_ADD_PROC(&d->play_sysctl_ctx,
	    SYSCTL_CHILDREN(d->play_sysctl_tree),
	    OID_AUTO, "vchans", CTLTYPE_INT | CTLFLAG_RWTUN,
	    VCHAN_SYSCTL_DATA(unit, PLAY), VCHAN_SYSCTL_DATA_SIZE,
	    sysctl_dev_pcm_vchans, "I", "total allocated virtual channel");
	SYSCTL_ADD_PROC(&d->play_sysctl_ctx,
	    SYSCTL_CHILDREN(d->play_sysctl_tree),
	    OID_AUTO, "vchanmode", CTLTYPE_STRING | CTLFLAG_RWTUN,
	    VCHAN_SYSCTL_DATA(unit, PLAY), VCHAN_SYSCTL_DATA_SIZE,
	    sysctl_dev_pcm_vchanmode, "A",
	    "vchan format/rate selection: 0=fixed, 1=passthrough, 2=adaptive");
	SYSCTL_ADD_PROC(&d->play_sysctl_ctx,
	    SYSCTL_CHILDREN(d->play_sysctl_tree),
	    OID_AUTO, "vchanrate", CTLTYPE_INT | CTLFLAG_RWTUN,
	    VCHAN_SYSCTL_DATA(unit, PLAY), VCHAN_SYSCTL_DATA_SIZE,
	    sysctl_dev_pcm_vchanrate, "I", "virtual channel mixing speed/rate");
	SYSCTL_ADD_PROC(&d->play_sysctl_ctx,
	    SYSCTL_CHILDREN(d->play_sysctl_tree),
	    OID_AUTO, "vchanformat", CTLTYPE_STRING | CTLFLAG_RWTUN,
	    VCHAN_SYSCTL_DATA(unit, PLAY), VCHAN_SYSCTL_DATA_SIZE,
	    sysctl_dev_pcm_vchanformat, "A", "virtual channel mixing format");
	/* Rec */
	SYSCTL_ADD_PROC(&d->rec_sysctl_ctx,
	    SYSCTL_CHILDREN(d->rec_sysctl_tree),
	    OID_AUTO, "vchans", CTLTYPE_INT | CTLFLAG_RWTUN,
	    VCHAN_SYSCTL_DATA(unit, REC), VCHAN_SYSCTL_DATA_SIZE,
	    sysctl_dev_pcm_vchans, "I", "total allocated virtual channel");
	SYSCTL_ADD_PROC(&d->rec_sysctl_ctx,
	    SYSCTL_CHILDREN(d->rec_sysctl_tree),
	    OID_AUTO, "vchanmode", CTLTYPE_STRING | CTLFLAG_RWTUN,
	    VCHAN_SYSCTL_DATA(unit, REC), VCHAN_SYSCTL_DATA_SIZE,
	    sysctl_dev_pcm_vchanmode, "A",
	    "vchan format/rate selection: 0=fixed, 1=passthrough, 2=adaptive");
	SYSCTL_ADD_PROC(&d->rec_sysctl_ctx,
	    SYSCTL_CHILDREN(d->rec_sysctl_tree),
	    OID_AUTO, "vchanrate", CTLTYPE_INT | CTLFLAG_RWTUN,
	    VCHAN_SYSCTL_DATA(unit, REC), VCHAN_SYSCTL_DATA_SIZE,
	    sysctl_dev_pcm_vchanrate, "I", "virtual channel mixing speed/rate");
	SYSCTL_ADD_PROC(&d->rec_sysctl_ctx,
	    SYSCTL_CHILDREN(d->rec_sysctl_tree),
	    OID_AUTO, "vchanformat", CTLTYPE_STRING | CTLFLAG_RWTUN,
	    VCHAN_SYSCTL_DATA(unit, REC), VCHAN_SYSCTL_DATA_SIZE,
	    sysctl_dev_pcm_vchanformat, "A", "virtual channel mixing format");
}