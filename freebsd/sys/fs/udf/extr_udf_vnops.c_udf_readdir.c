#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct vop_readdir_args {int* a_eofflag; int /*<<< orphan*/ ** a_cookies; scalar_t__* a_ncookies; struct uio* a_uio; struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
struct uio {int uio_resid; scalar_t__ uio_offset; } ;
struct udf_uiodir {int eofflag; int ncookies; scalar_t__ acookies; struct dirent* dirent; int /*<<< orphan*/ * cookies; } ;
struct udf_node {void* hash_id; struct udf_mnt* udfmp; TYPE_1__* fentry; } ;
struct udf_mnt {int dummy; } ;
struct udf_dirstream {int this_off; int error; scalar_t__ off; scalar_t__ offset; } ;
struct fileid_desc {int file_char; scalar_t__ l_fi; size_t l_iu; int /*<<< orphan*/  icb; int /*<<< orphan*/ * data; int /*<<< orphan*/  tag; } ;
struct dirent {char* d_name; int d_namlen; int d_off; void* d_reclen; void* d_type; void* d_fileno; } ;
struct TYPE_2__ {int /*<<< orphan*/  inf_len; } ;

/* Variables and functions */
 void* DT_DIR ; 
 void* DT_UNKNOWN ; 
 int EIO ; 
 int ENOMEM ; 
 void* GENERIC_DIRSIZ (struct dirent*) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  TAGID_FID ; 
 int /*<<< orphan*/  UDF_FID_SIZE ; 
 int UDF_FILE_CHAR_DEL ; 
 int UDF_FILE_CHAR_DIR ; 
 int UDF_FILE_CHAR_PAR ; 
 struct udf_node* VTON (struct vnode*) ; 
 int /*<<< orphan*/  dirent_terminate (struct dirent*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hexdump (struct fileid_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ udf_checktag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_closedir (struct udf_dirstream*) ; 
 struct fileid_desc* udf_getfid (struct udf_dirstream*) ; 
 void* udf_getid (int /*<<< orphan*/ *) ; 
 struct udf_dirstream* udf_opendir (struct udf_node*,scalar_t__,int /*<<< orphan*/ ,struct udf_mnt*) ; 
 int udf_transname (int /*<<< orphan*/ *,char*,scalar_t__,struct udf_mnt*) ; 
 int udf_uiodir (struct udf_uiodir*,void*,struct uio*,int) ; 

__attribute__((used)) static int
udf_readdir(struct vop_readdir_args *a)
{
	struct vnode *vp;
	struct uio *uio;
	struct dirent dir;
	struct udf_node *node;
	struct udf_mnt *udfmp;
	struct fileid_desc *fid;
	struct udf_uiodir uiodir;
	struct udf_dirstream *ds;
	u_long *cookies = NULL;
	int ncookies;
	int error = 0;

	vp = a->a_vp;
	uio = a->a_uio;
	node = VTON(vp);
	udfmp = node->udfmp;
	uiodir.eofflag = 1;

	if (a->a_ncookies != NULL) {
		/*
		 * Guess how many entries are needed.  If we run out, this
		 * function will be called again and thing will pick up were
		 * it left off.
		 */
		ncookies = uio->uio_resid / 8;
		cookies = malloc(sizeof(u_long) * ncookies,
		    M_TEMP, M_WAITOK);
		if (cookies == NULL)
			return (ENOMEM);
		uiodir.ncookies = ncookies;
		uiodir.cookies = cookies;
		uiodir.acookies = 0;
	} else {
		uiodir.cookies = NULL;
	}

	/*
	 * Iterate through the file id descriptors.  Give the parent dir
	 * entry special attention.
	 */
	ds = udf_opendir(node, uio->uio_offset, le64toh(node->fentry->inf_len),
	    node->udfmp);

	while ((fid = udf_getfid(ds)) != NULL) {

		/* XXX Should we return an error on a bad fid? */
		if (udf_checktag(&fid->tag, TAGID_FID)) {
			printf("Invalid FID tag\n");
			hexdump(fid, UDF_FID_SIZE, NULL, 0);
			error = EIO;
			break;
		}

		/* Is this a deleted file? */
		if (fid->file_char & UDF_FILE_CHAR_DEL)
			continue;

		if ((fid->l_fi == 0) && (fid->file_char & UDF_FILE_CHAR_PAR)) {
			/* Do up the '.' and '..' entries.  Dummy values are
			 * used for the cookies since the offset here is
			 * usually zero, and NFS doesn't like that value
			 */
			dir.d_fileno = node->hash_id;
			dir.d_type = DT_DIR;
			dir.d_name[0] = '.';
			dir.d_namlen = 1;
			dir.d_reclen = GENERIC_DIRSIZ(&dir);
			dir.d_off = 1;
			dirent_terminate(&dir);
			uiodir.dirent = &dir;
			error = udf_uiodir(&uiodir, dir.d_reclen, uio, 1);
			if (error)
				break;

			dir.d_fileno = udf_getid(&fid->icb);
			dir.d_type = DT_DIR;
			dir.d_name[0] = '.';
			dir.d_name[1] = '.';
			dir.d_namlen = 2;
			dir.d_reclen = GENERIC_DIRSIZ(&dir);
			dir.d_off = 2;
			dirent_terminate(&dir);
			uiodir.dirent = &dir;
			error = udf_uiodir(&uiodir, dir.d_reclen, uio, 2);
		} else {
			dir.d_namlen = udf_transname(&fid->data[fid->l_iu],
			    &dir.d_name[0], fid->l_fi, udfmp);
			dir.d_fileno = udf_getid(&fid->icb);
			dir.d_type = (fid->file_char & UDF_FILE_CHAR_DIR) ?
			    DT_DIR : DT_UNKNOWN;
			dir.d_reclen = GENERIC_DIRSIZ(&dir);
			dir.d_off = ds->this_off;
			dirent_terminate(&dir);
			uiodir.dirent = &dir;
			error = udf_uiodir(&uiodir, dir.d_reclen, uio,
			    ds->this_off);
		}
		if (error)
			break;
		uio->uio_offset = ds->offset + ds->off;
	}

	/* tell the calling layer whether we need to be called again */
	*a->a_eofflag = uiodir.eofflag;

	if (error < 0)
		error = 0;
	if (!error)
		error = ds->error;

	udf_closedir(ds);

	if (a->a_ncookies != NULL) {
		if (error)
			free(cookies, M_TEMP);
		else {
			*a->a_ncookies = uiodir.acookies;
			*a->a_cookies = cookies;
		}
	}

	return (error);
}