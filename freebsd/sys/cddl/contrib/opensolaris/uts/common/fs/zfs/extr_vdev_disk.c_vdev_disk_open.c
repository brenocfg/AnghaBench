#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {void* vs_aux; } ;
struct TYPE_12__ {char* vdev_path; char* vdev_devid; unsigned long long vdev_wholedisk; char* vdev_physpath; void* vdev_nowritecache; TYPE_1__ vdev_stat; TYPE_3__* vdev_tsd; int /*<<< orphan*/  vdev_reopening; int /*<<< orphan*/ * vdev_spa; } ;
typedef  TYPE_2__ vdev_t ;
struct TYPE_13__ {int /*<<< orphan*/ * vd_lh; int /*<<< orphan*/  vd_ldi_cbs; int /*<<< orphan*/  vd_minor; int /*<<< orphan*/  vd_devid; scalar_t__ vd_ldi_offline; } ;
typedef  TYPE_3__ vdev_disk_t ;
struct TYPE_14__ {int /*<<< orphan*/  lcb_id; } ;
typedef  TYPE_4__ vdev_disk_ldi_cb_t ;
typedef  int uint64_t ;
struct dk_minfo_ext {int dki_capacity; int dki_lbsize; int dki_pbsize; } ;
struct dk_minfo {int dki_capacity; int dki_lbsize; } ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  ldi_ev_cookie_t ;
typedef  int /*<<< orphan*/  dev_t ;
typedef  int /*<<< orphan*/  ddi_devid_t ;
typedef  void* boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 void* B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  CE_NOTE ; 
 int DEV_BSIZE ; 
 int /*<<< orphan*/  DKIOCGMEDIAINFO ; 
 int /*<<< orphan*/  DKIOCGMEDIAINFOEXT ; 
 int /*<<< orphan*/  DKIOCSETWCE ; 
 int EINVAL ; 
 int /*<<< orphan*/  FKIOCTL ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  LDI_EV_DEGRADE ; 
 int /*<<< orphan*/  LDI_EV_OFFLINE ; 
 scalar_t__ LDI_EV_SUCCESS ; 
 int /*<<< orphan*/  MAX (int,int /*<<< orphan*/ ) ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  NODEV ; 
 int /*<<< orphan*/  OTYP_BLK ; 
 int SET_ERROR (int) ; 
 int /*<<< orphan*/  SPA_MINBLOCKSIZE ; 
 void* VDEV_AUX_BAD_LABEL ; 
 void* VDEV_AUX_OPEN_FAILED ; 
 int /*<<< orphan*/  VDEV_DEBUG (char*,char*,...) ; 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 scalar_t__ ddi_dev_pathname (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ ddi_devid_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddi_devid_free (int /*<<< orphan*/ ) ; 
 scalar_t__ ddi_devid_str_decode (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* ddi_devid_str_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddi_devid_str_free (char*) ; 
 int /*<<< orphan*/  ddi_pathname_to_dev_t (char*) ; 
 int highbit64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcred ; 
 char* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*,int) ; 
 TYPE_4__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldi_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ldi_ev_get_cookie (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldi_ev_register_callbacks (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ ldi_get_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ldi_get_devid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ldi_get_minor_name (int /*<<< orphan*/ *,char**) ; 
 scalar_t__ ldi_get_otyp (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ ldi_get_size (int /*<<< orphan*/ *,int*) ; 
 int ldi_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,intptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ldi_open_by_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int ldi_open_by_devid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int ldi_open_by_name (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_insert_tail (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 
 int /*<<< orphan*/  spa_mode (int /*<<< orphan*/ *) ; 
 void* spa_strdup (char*) ; 
 int /*<<< orphan*/  spa_strfree (char*) ; 
 scalar_t__ spa_writeable (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  vdev_dbgmsg (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  vdev_disk_alloc (TYPE_2__*) ; 
 scalar_t__ vdev_disk_bypass_devid ; 
 int /*<<< orphan*/  vdev_disk_dgrd_callb ; 
 int /*<<< orphan*/  vdev_disk_free (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_disk_off_callb ; 
 int /*<<< orphan*/  zfs_li ; 

__attribute__((used)) static int
vdev_disk_open(vdev_t *vd, uint64_t *psize, uint64_t *max_psize,
    uint64_t *ashift)
{
	spa_t *spa = vd->vdev_spa;
	vdev_disk_t *dvd = vd->vdev_tsd;
	ldi_ev_cookie_t ecookie;
	vdev_disk_ldi_cb_t *lcb;
	union {
		struct dk_minfo_ext ude;
		struct dk_minfo ud;
	} dks;
	struct dk_minfo_ext *dkmext = &dks.ude;
	struct dk_minfo *dkm = &dks.ud;
	int error;
	dev_t dev;
	int otyp;
	boolean_t validate_devid = B_FALSE;
	ddi_devid_t devid;
	uint64_t capacity = 0, blksz = 0, pbsize;

	/*
	 * We must have a pathname, and it must be absolute.
	 */
	if (vd->vdev_path == NULL || vd->vdev_path[0] != '/') {
		vd->vdev_stat.vs_aux = VDEV_AUX_BAD_LABEL;
		return (SET_ERROR(EINVAL));
	}

	/*
	 * Reopen the device if it's not currently open. Otherwise,
	 * just update the physical size of the device.
	 */
	if (dvd != NULL) {
		if (dvd->vd_ldi_offline && dvd->vd_lh == NULL) {
			/*
			 * If we are opening a device in its offline notify
			 * context, the LDI handle was just closed. Clean
			 * up the LDI event callbacks and free vd->vdev_tsd.
			 */
			vdev_disk_free(vd);
		} else {
			ASSERT(vd->vdev_reopening);
			goto skip_open;
		}
	}

	/*
	 * Create vd->vdev_tsd.
	 */
	vdev_disk_alloc(vd);
	dvd = vd->vdev_tsd;

	/*
	 * Allow bypassing the devid.
	 */
	if (vd->vdev_devid != NULL && vdev_disk_bypass_devid) {
		vdev_dbgmsg(vd, "vdev_disk_open, devid %s bypassed",
		    vd->vdev_devid);
		spa_strfree(vd->vdev_devid);
		vd->vdev_devid = NULL;
	}

	/*
	 * When opening a disk device, we want to preserve the user's original
	 * intent.  We always want to open the device by the path the user gave
	 * us, even if it is one of multiple paths to the save device.  But we
	 * also want to be able to survive disks being removed/recabled.
	 * Therefore the sequence of opening devices is:
	 *
	 * 1. Try opening the device by path.  For legacy pools without the
	 *    'whole_disk' property, attempt to fix the path by appending 's0'.
	 *
	 * 2. If the devid of the device matches the stored value, return
	 *    success.
	 *
	 * 3. Otherwise, the device may have moved.  Try opening the device
	 *    by the devid instead.
	 */
	if (vd->vdev_devid != NULL) {
		if (ddi_devid_str_decode(vd->vdev_devid, &dvd->vd_devid,
		    &dvd->vd_minor) != 0) {
			vd->vdev_stat.vs_aux = VDEV_AUX_BAD_LABEL;
			vdev_dbgmsg(vd, "vdev_disk_open: invalid "
			    "vdev_devid '%s'", vd->vdev_devid);
			return (SET_ERROR(EINVAL));
		}
	}

	error = EINVAL;		/* presume failure */

	if (vd->vdev_path != NULL) {

		if (vd->vdev_wholedisk == -1ULL) {
			size_t len = strlen(vd->vdev_path) + 3;
			char *buf = kmem_alloc(len, KM_SLEEP);

			(void) snprintf(buf, len, "%ss0", vd->vdev_path);

			error = ldi_open_by_name(buf, spa_mode(spa), kcred,
			    &dvd->vd_lh, zfs_li);
			if (error == 0) {
				spa_strfree(vd->vdev_path);
				vd->vdev_path = buf;
				vd->vdev_wholedisk = 1ULL;
			} else {
				kmem_free(buf, len);
			}
		}

		/*
		 * If we have not yet opened the device, try to open it by the
		 * specified path.
		 */
		if (error != 0) {
			error = ldi_open_by_name(vd->vdev_path, spa_mode(spa),
			    kcred, &dvd->vd_lh, zfs_li);
		}

		/*
		 * Compare the devid to the stored value.
		 */
		if (error == 0 && vd->vdev_devid != NULL &&
		    ldi_get_devid(dvd->vd_lh, &devid) == 0) {
			if (ddi_devid_compare(devid, dvd->vd_devid) != 0) {
				/*
				 * A mismatch here is unexpected, log it.
				 */
				char *devid_str = ddi_devid_str_encode(devid,
				    dvd->vd_minor);
				vdev_dbgmsg(vd, "vdev_disk_open: devid "
				    "mismatch: %s != %s", vd->vdev_devid,
				    devid_str);
				cmn_err(CE_NOTE, "vdev_disk_open %s: devid "
				    "mismatch: %s != %s", vd->vdev_path,
				    vd->vdev_devid, devid_str);
				ddi_devid_str_free(devid_str);

				error = SET_ERROR(EINVAL);
				(void) ldi_close(dvd->vd_lh, spa_mode(spa),
				    kcred);
				dvd->vd_lh = NULL;
			}
			ddi_devid_free(devid);
		}

		/*
		 * If we succeeded in opening the device, but 'vdev_wholedisk'
		 * is not yet set, then this must be a slice.
		 */
		if (error == 0 && vd->vdev_wholedisk == -1ULL)
			vd->vdev_wholedisk = 0;
	}

	/*
	 * If we were unable to open by path, or the devid check fails, open by
	 * devid instead.
	 */
	if (error != 0 && vd->vdev_devid != NULL) {
		error = ldi_open_by_devid(dvd->vd_devid, dvd->vd_minor,
		    spa_mode(spa), kcred, &dvd->vd_lh, zfs_li);
		if (error != 0) {
			vdev_dbgmsg(vd, "Failed to open by devid (%s)",
			    vd->vdev_devid);
		}
	}

	/*
	 * If all else fails, then try opening by physical path (if available)
	 * or the logical path (if we failed due to the devid check).  While not
	 * as reliable as the devid, this will give us something, and the higher
	 * level vdev validation will prevent us from opening the wrong device.
	 */
	if (error) {
		if (vd->vdev_devid != NULL)
			validate_devid = B_TRUE;

		if (vd->vdev_physpath != NULL &&
		    (dev = ddi_pathname_to_dev_t(vd->vdev_physpath)) != NODEV)
			error = ldi_open_by_dev(&dev, OTYP_BLK, spa_mode(spa),
			    kcred, &dvd->vd_lh, zfs_li);

		/*
		 * Note that we don't support the legacy auto-wholedisk support
		 * as above.  This hasn't been used in a very long time and we
		 * don't need to propagate its oddities to this edge condition.
		 */
		if (error && vd->vdev_path != NULL)
			error = ldi_open_by_name(vd->vdev_path, spa_mode(spa),
			    kcred, &dvd->vd_lh, zfs_li);
	}

	if (error) {
		vd->vdev_stat.vs_aux = VDEV_AUX_OPEN_FAILED;
		vdev_dbgmsg(vd, "vdev_disk_open: failed to open [error=%d]",
		    error);
		return (error);
	}

	/*
	 * Now that the device has been successfully opened, update the devid
	 * if necessary.
	 */
	if (validate_devid && spa_writeable(spa) &&
	    ldi_get_devid(dvd->vd_lh, &devid) == 0) {
		if (ddi_devid_compare(devid, dvd->vd_devid) != 0) {
			char *vd_devid;

			vd_devid = ddi_devid_str_encode(devid, dvd->vd_minor);
			vdev_dbgmsg(vd, "vdev_disk_open: update devid from "
			    "'%s' to '%s'", vd->vdev_devid, vd_devid);
			cmn_err(CE_NOTE, "vdev_disk_open %s: update devid "
			    "from '%s' to '%s'", vd->vdev_path != NULL ?
			    vd->vdev_path : "?", vd->vdev_devid, vd_devid);
			spa_strfree(vd->vdev_devid);
			vd->vdev_devid = spa_strdup(vd_devid);
			ddi_devid_str_free(vd_devid);
		}
		ddi_devid_free(devid);
	}

	/*
	 * Once a device is opened, verify that the physical device path (if
	 * available) is up to date.
	 */
	if (ldi_get_dev(dvd->vd_lh, &dev) == 0 &&
	    ldi_get_otyp(dvd->vd_lh, &otyp) == 0) {
		char *physpath, *minorname;

		physpath = kmem_alloc(MAXPATHLEN, KM_SLEEP);
		minorname = NULL;
		if (ddi_dev_pathname(dev, otyp, physpath) == 0 &&
		    ldi_get_minor_name(dvd->vd_lh, &minorname) == 0 &&
		    (vd->vdev_physpath == NULL ||
		    strcmp(vd->vdev_physpath, physpath) != 0)) {
			if (vd->vdev_physpath)
				spa_strfree(vd->vdev_physpath);
			(void) strlcat(physpath, ":", MAXPATHLEN);
			(void) strlcat(physpath, minorname, MAXPATHLEN);
			vd->vdev_physpath = spa_strdup(physpath);
		}
		if (minorname)
			kmem_free(minorname, strlen(minorname) + 1);
		kmem_free(physpath, MAXPATHLEN);
	}

	/*
	 * Register callbacks for the LDI offline event.
	 */
	if (ldi_ev_get_cookie(dvd->vd_lh, LDI_EV_OFFLINE, &ecookie) ==
	    LDI_EV_SUCCESS) {
		lcb = kmem_zalloc(sizeof (vdev_disk_ldi_cb_t), KM_SLEEP);
		list_insert_tail(&dvd->vd_ldi_cbs, lcb);
		(void) ldi_ev_register_callbacks(dvd->vd_lh, ecookie,
		    &vdev_disk_off_callb, (void *) vd, &lcb->lcb_id);
	}

	/*
	 * Register callbacks for the LDI degrade event.
	 */
	if (ldi_ev_get_cookie(dvd->vd_lh, LDI_EV_DEGRADE, &ecookie) ==
	    LDI_EV_SUCCESS) {
		lcb = kmem_zalloc(sizeof (vdev_disk_ldi_cb_t), KM_SLEEP);
		list_insert_tail(&dvd->vd_ldi_cbs, lcb);
		(void) ldi_ev_register_callbacks(dvd->vd_lh, ecookie,
		    &vdev_disk_dgrd_callb, (void *) vd, &lcb->lcb_id);
	}
skip_open:
	/*
	 * Determine the actual size of the device.
	 */
	if (ldi_get_size(dvd->vd_lh, psize) != 0) {
		vd->vdev_stat.vs_aux = VDEV_AUX_OPEN_FAILED;
		vdev_dbgmsg(vd, "vdev_disk_open: failed to get size");
		return (SET_ERROR(EINVAL));
	}

	*max_psize = *psize;

	/*
	 * Determine the device's minimum transfer size.
	 * If the ioctl isn't supported, assume DEV_BSIZE.
	 */
	if ((error = ldi_ioctl(dvd->vd_lh, DKIOCGMEDIAINFOEXT,
	    (intptr_t)dkmext, FKIOCTL, kcred, NULL)) == 0) {
		capacity = dkmext->dki_capacity - 1;
		blksz = dkmext->dki_lbsize;
		pbsize = dkmext->dki_pbsize;
	} else if ((error = ldi_ioctl(dvd->vd_lh, DKIOCGMEDIAINFO,
	    (intptr_t)dkm, FKIOCTL, kcred, NULL)) == 0) {
		VDEV_DEBUG(
		    "vdev_disk_open(\"%s\"): fallback to DKIOCGMEDIAINFO\n",
		    vd->vdev_path);
		capacity = dkm->dki_capacity - 1;
		blksz = dkm->dki_lbsize;
		pbsize = blksz;
	} else {
		VDEV_DEBUG("vdev_disk_open(\"%s\"): "
		    "both DKIOCGMEDIAINFO{,EXT} calls failed, %d\n",
		    vd->vdev_path, error);
		pbsize = DEV_BSIZE;
	}

	*ashift = highbit64(MAX(pbsize, SPA_MINBLOCKSIZE)) - 1;

	if (vd->vdev_wholedisk == 1) {
		int wce = 1;

		if (error == 0) {
			/*
			 * If we have the capability to expand, we'd have
			 * found out via success from DKIOCGMEDIAINFO{,EXT}.
			 * Adjust max_psize upward accordingly since we know
			 * we own the whole disk now.
			 */
			*max_psize = capacity * blksz;
		}

		/*
		 * Since we own the whole disk, try to enable disk write
		 * caching.  We ignore errors because it's OK if we can't do it.
		 */
		(void) ldi_ioctl(dvd->vd_lh, DKIOCSETWCE, (intptr_t)&wce,
		    FKIOCTL, kcred, NULL);
	}

	/*
	 * Clear the nowritecache bit, so that on a vdev_reopen() we will
	 * try again.
	 */
	vd->vdev_nowritecache = B_FALSE;

	return (0);
}