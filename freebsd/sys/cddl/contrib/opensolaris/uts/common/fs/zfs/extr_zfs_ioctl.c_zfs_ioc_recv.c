#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  z_vfs; int /*<<< orphan*/  z_os; } ;
typedef  TYPE_1__ zfsvfs_t ;
struct TYPE_18__ {char* zc_value; scalar_t__ zc_nvlist_src; int zc_cookie; char* zc_string; int /*<<< orphan*/  zc_obj; int /*<<< orphan*/  zc_nvlist_dst_size; int /*<<< orphan*/  zc_action_handle; int /*<<< orphan*/  zc_cleanup_fd; int /*<<< orphan*/  zc_resumable; int /*<<< orphan*/  zc_begin_record; int /*<<< orphan*/  zc_iflags; int /*<<< orphan*/  zc_nvlist_src_size; int /*<<< orphan*/  zc_guid; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  scalar_t__ offset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_19__ {scalar_t__ f_offset; } ;
typedef  TYPE_3__ file_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
struct TYPE_20__ {int /*<<< orphan*/  drc_newfs; int /*<<< orphan*/  drc_ds; } ;
typedef  TYPE_4__ dmu_recv_cookie_t ;
typedef  void* boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 void* B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ MAXOFFSET_T ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ SPA_VERSION_RECVD_PROPS ; 
 int /*<<< orphan*/  VFS_RELE (int /*<<< orphan*/ ) ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZPROP_ERR_NOCLEAR ; 
 int /*<<< orphan*/  ZPROP_ERR_NORESTORE ; 
 int /*<<< orphan*/  ZPROP_SRC_LOCAL ; 
 int /*<<< orphan*/  ZPROP_SRC_RECEIVED ; 
 int /*<<< orphan*/  cap_pread_rights ; 
 scalar_t__ clear_received_props (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curthread ; 
 scalar_t__ dataset_namecheck (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_objset_ds (int /*<<< orphan*/ ) ; 
 int dmu_recv_begin (char*,char*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 int dmu_recv_end (TYPE_4__*,TYPE_1__*) ; 
 int dmu_recv_stream (TYPE_4__*,TYPE_3__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_get_spa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_prop_get_hasrecvd (char*) ; 
 scalar_t__ dsl_prop_get_received (char*,int /*<<< orphan*/ **) ; 
 int dsl_prop_set_hasrecvd (char*) ; 
 int /*<<< orphan*/  dsl_prop_unset_hasrecvd (char*) ; 
 int /*<<< orphan*/ * extract_delay_props (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fget_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int get_nvlist (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 TYPE_3__* getf (int) ; 
 scalar_t__ getzfsvfs (char*,TYPE_1__**) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_smush (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  props_reduce (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ put_nvlist (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  releasef (int) ; 
 scalar_t__ spa_version (int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  vfs_unbusy (int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_check_clearable (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 void* zfs_ioc_recv_inject_err ; 
 int zfs_resume_fs (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_set_prop_nvlist (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zfs_suspend_fs (TYPE_1__*) ; 
 int /*<<< orphan*/  zvol_create_minors (char*) ; 

__attribute__((used)) static int
zfs_ioc_recv(zfs_cmd_t *zc)
{
	file_t *fp;
	dmu_recv_cookie_t drc;
	boolean_t force = (boolean_t)zc->zc_guid;
	int fd;
	int error = 0;
	int props_error = 0;
	nvlist_t *errors;
	offset_t off;
	nvlist_t *props = NULL; /* sent properties */
	nvlist_t *origprops = NULL; /* existing properties */
	nvlist_t *delayprops = NULL; /* sent properties applied post-receive */
	char *origin = NULL;
	char *tosnap;
	char tofs[ZFS_MAX_DATASET_NAME_LEN];
	boolean_t first_recvd_props = B_FALSE;

	if (dataset_namecheck(zc->zc_value, NULL, NULL) != 0 ||
	    strchr(zc->zc_value, '@') == NULL ||
	    strchr(zc->zc_value, '%'))
		return (SET_ERROR(EINVAL));

	(void) strcpy(tofs, zc->zc_value);
	tosnap = strchr(tofs, '@');
	*tosnap++ = '\0';

	if (zc->zc_nvlist_src != 0 &&
	    (error = get_nvlist(zc->zc_nvlist_src, zc->zc_nvlist_src_size,
	    zc->zc_iflags, &props)) != 0)
		return (error);

	fd = zc->zc_cookie;
#ifdef illumos
	fp = getf(fd);
#else
	fget_read(curthread, fd, &cap_pread_rights, &fp);
#endif
	if (fp == NULL) {
		nvlist_free(props);
		return (SET_ERROR(EBADF));
	}

	errors = fnvlist_alloc();

	if (zc->zc_string[0])
		origin = zc->zc_string;

	error = dmu_recv_begin(tofs, tosnap,
	    &zc->zc_begin_record, force, zc->zc_resumable, origin, &drc);
	if (error != 0)
		goto out;

	/*
	 * Set properties before we receive the stream so that they are applied
	 * to the new data. Note that we must call dmu_recv_stream() if
	 * dmu_recv_begin() succeeds.
	 */
	if (props != NULL && !drc.drc_newfs) {
		if (spa_version(dsl_dataset_get_spa(drc.drc_ds)) >=
		    SPA_VERSION_RECVD_PROPS &&
		    !dsl_prop_get_hasrecvd(tofs))
			first_recvd_props = B_TRUE;

		/*
		 * If new received properties are supplied, they are to
		 * completely replace the existing received properties, so stash
		 * away the existing ones.
		 */
		if (dsl_prop_get_received(tofs, &origprops) == 0) {
			nvlist_t *errlist = NULL;
			/*
			 * Don't bother writing a property if its value won't
			 * change (and avoid the unnecessary security checks).
			 *
			 * The first receive after SPA_VERSION_RECVD_PROPS is a
			 * special case where we blow away all local properties
			 * regardless.
			 */
			if (!first_recvd_props)
				props_reduce(props, origprops);
			if (zfs_check_clearable(tofs, origprops, &errlist) != 0)
				(void) nvlist_merge(errors, errlist, 0);
			nvlist_free(errlist);

			if (clear_received_props(tofs, origprops,
			    first_recvd_props ? NULL : props) != 0)
				zc->zc_obj |= ZPROP_ERR_NOCLEAR;
		} else {
			zc->zc_obj |= ZPROP_ERR_NOCLEAR;
		}
	}

	if (props != NULL) {
		props_error = dsl_prop_set_hasrecvd(tofs);

		if (props_error == 0) {
			delayprops = extract_delay_props(props);
			(void) zfs_set_prop_nvlist(tofs, ZPROP_SRC_RECEIVED,
			    props, errors);
		}
	}

	off = fp->f_offset;
	error = dmu_recv_stream(&drc, fp, &off, zc->zc_cleanup_fd,
	    &zc->zc_action_handle);

	if (error == 0) {
		zfsvfs_t *zfsvfs = NULL;

		if (getzfsvfs(tofs, &zfsvfs) == 0) {
			/* online recv */
			dsl_dataset_t *ds;
			int end_err;

			ds = dmu_objset_ds(zfsvfs->z_os);
			error = zfs_suspend_fs(zfsvfs);
			/*
			 * If the suspend fails, then the recv_end will
			 * likely also fail, and clean up after itself.
			 */
			end_err = dmu_recv_end(&drc, zfsvfs);
			if (error == 0)
				error = zfs_resume_fs(zfsvfs, ds);
			error = error ? error : end_err;
#ifdef illumos
			VFS_RELE(zfsvfs->z_vfs);
#else
			vfs_unbusy(zfsvfs->z_vfs);
#endif
		} else {
			error = dmu_recv_end(&drc, NULL);
		}

		/* Set delayed properties now, after we're done receiving. */
		if (delayprops != NULL && error == 0) {
			(void) zfs_set_prop_nvlist(tofs, ZPROP_SRC_RECEIVED,
			    delayprops, errors);
		}
	}

	if (delayprops != NULL) {
		/*
		 * Merge delayed props back in with initial props, in case
		 * we're DEBUG and zfs_ioc_recv_inject_err is set (which means
		 * we have to make sure clear_received_props() includes
		 * the delayed properties).
		 *
		 * Since zfs_ioc_recv_inject_err is only in DEBUG kernels,
		 * using ASSERT() will be just like a VERIFY.
		 */
		ASSERT(nvlist_merge(props, delayprops, 0) == 0);
		nvlist_free(delayprops);
	}

	/*
	 * Now that all props, initial and delayed, are set, report the prop
	 * errors to the caller.
	 */
	if (zc->zc_nvlist_dst_size != 0 &&
	    (nvlist_smush(errors, zc->zc_nvlist_dst_size) != 0 ||
	    put_nvlist(zc, errors) != 0)) {
		/*
		 * Caller made zc->zc_nvlist_dst less than the minimum expected
		 * size or supplied an invalid address.
		 */
		props_error = SET_ERROR(EINVAL);
	}

	zc->zc_cookie = off - fp->f_offset;
	if (off >= 0 && off <= MAXOFFSET_T)
		fp->f_offset = off;

#ifdef	DEBUG
	if (zfs_ioc_recv_inject_err) {
		zfs_ioc_recv_inject_err = B_FALSE;
		error = 1;
	}
#endif

#ifdef __FreeBSD__
	if (error == 0)
		zvol_create_minors(tofs);
#endif

	/*
	 * On error, restore the original props.
	 */
	if (error != 0 && props != NULL && !drc.drc_newfs) {
		if (clear_received_props(tofs, props, NULL) != 0) {
			/*
			 * We failed to clear the received properties.
			 * Since we may have left a $recvd value on the
			 * system, we can't clear the $hasrecvd flag.
			 */
			zc->zc_obj |= ZPROP_ERR_NORESTORE;
		} else if (first_recvd_props) {
			dsl_prop_unset_hasrecvd(tofs);
		}

		if (origprops == NULL && !drc.drc_newfs) {
			/* We failed to stash the original properties. */
			zc->zc_obj |= ZPROP_ERR_NORESTORE;
		}

		/*
		 * dsl_props_set() will not convert RECEIVED to LOCAL on or
		 * after SPA_VERSION_RECVD_PROPS, so we need to specify LOCAL
		 * explictly if we're restoring local properties cleared in the
		 * first new-style receive.
		 */
		if (origprops != NULL &&
		    zfs_set_prop_nvlist(tofs, (first_recvd_props ?
		    ZPROP_SRC_LOCAL : ZPROP_SRC_RECEIVED),
		    origprops, NULL) != 0) {
			/*
			 * We stashed the original properties but failed to
			 * restore them.
			 */
			zc->zc_obj |= ZPROP_ERR_NORESTORE;
		}
	}
out:
	nvlist_free(props);
	nvlist_free(origprops);
	nvlist_free(errors);
	releasef(fd);

	if (error == 0)
		error = props_error;

	return (error);
}