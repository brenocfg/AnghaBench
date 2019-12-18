#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vattr {int va_mode; int /*<<< orphan*/  va_gen; int /*<<< orphan*/  va_fileid; int /*<<< orphan*/  va_fsid; } ;
struct nameidata {int /*<<< orphan*/  ni_vp; } ;
struct TYPE_3__ {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FREAD ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int VEXEC ; 
 int VOP_GETATTR (int /*<<< orphan*/ ,struct vattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_UNLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* curthread ; 
 int get_fp (char*,char**,unsigned char**,int*) ; 
 int hexstring_to_bin (unsigned char*) ; 
 int mac_veriexec_metadata_add_file (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int open_file (char*,struct nameidata*) ; 
 int snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strnlen (char*,int) ; 
 int /*<<< orphan*/  ve_mutex ; 
 int /*<<< orphan*/  vn_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
parse_entry(char *entry, char *prefix)
{
	struct nameidata	nid;
	struct vattr		va;
	char			path[MAXPATHLEN];
	char			*fp_type;
	unsigned char		*digest;
	int			rc, is_exec, flags;

	fp_type = NULL;
	digest = NULL;
	flags = 0;

	rc = get_fp(entry, &fp_type, &digest, &flags);
	if (rc != 0)
		return (rc);

	rc = hexstring_to_bin(digest);
	if (rc != 0)
		return (rc);

	if (strnlen(entry, MAXPATHLEN) == MAXPATHLEN)
		return (EINVAL);

	/* If the path is not absolute prepend it with a prefix */
	if (prefix != NULL && entry[0] != '/') {
		rc = snprintf(path, MAXPATHLEN, "%s/%s",
			    prefix, entry);
		if (rc < 0)
			return (-rc);
	} else {
		strcpy(path, entry);
	}

	rc = open_file(path, &nid);
	NDFREE(&nid, NDF_ONLY_PNBUF);
	if (rc != 0)
		return (rc);

	rc = VOP_GETATTR(nid.ni_vp, &va, curthread->td_ucred);
	if (rc != 0)
		goto out;

	is_exec = (va.va_mode & VEXEC);

	mtx_lock(&ve_mutex);
	rc = mac_veriexec_metadata_add_file(
	    is_exec == 0,
	    va.va_fsid, va.va_fileid, va.va_gen,
	    digest,
	    NULL, 0,
	    flags, fp_type, 1);
	mtx_unlock(&ve_mutex);

out:
	VOP_UNLOCK(nid.ni_vp, 0);
	vn_close(nid.ni_vp, FREAD, curthread->td_ucred, curthread);
	return (rc);
}