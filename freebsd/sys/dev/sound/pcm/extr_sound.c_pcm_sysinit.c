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
struct snddev_info {int flags; int /*<<< orphan*/  bufsz; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  d ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int CTLFLAG_RWTUN ; 
 int CTLTYPE_INT ; 
 int CTLTYPE_UINT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int SD_F_AUTOVCHAN ; 
 int SD_F_EQ ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct snddev_info*,int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 struct snddev_info* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  feeder_eq_initsys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_dev_pcm_bitperfect ; 
 int /*<<< orphan*/  sysctl_dev_pcm_clone_deadline ; 
 int /*<<< orphan*/  sysctl_dev_pcm_clone_flags ; 
 int /*<<< orphan*/  sysctl_dev_pcm_clone_gc ; 
 int /*<<< orphan*/  vchan_initsys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pcm_sysinit(device_t dev)
{
  	struct snddev_info *d = device_get_softc(dev);

  	/* XXX: an user should be able to set this with a control tool, the
	   sysadmin then needs min+max sysctls for this */
	SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
            OID_AUTO, "buffersize", CTLFLAG_RD, &d->bufsz, 0, "allocated buffer size");
	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)), OID_AUTO,
	    "bitperfect", CTLTYPE_INT | CTLFLAG_RWTUN, d, sizeof(d),
	    sysctl_dev_pcm_bitperfect, "I",
	    "bit-perfect playback/recording (0=disable, 1=enable)");
#ifdef SND_DEBUG
	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)), OID_AUTO,
	    "clone_flags", CTLTYPE_UINT | CTLFLAG_RWTUN, d, sizeof(d),
	    sysctl_dev_pcm_clone_flags, "IU",
	    "clone flags");
	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)), OID_AUTO,
	    "clone_deadline", CTLTYPE_INT | CTLFLAG_RWTUN, d, sizeof(d),
	    sysctl_dev_pcm_clone_deadline, "I",
	    "clone expiration deadline (ms)");
	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)), OID_AUTO,
	    "clone_gc", CTLTYPE_INT | CTLFLAG_RWTUN, d, sizeof(d),
	    sysctl_dev_pcm_clone_gc, "I",
	    "clone garbage collector");
#endif
	if (d->flags & SD_F_AUTOVCHAN)
		vchan_initsys(dev);
	if (d->flags & SD_F_EQ)
		feeder_eq_initsys(dev);
}