#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vattr {size_t va_size; } ;
struct nameidata {int /*<<< orphan*/  ni_vp; } ;
typedef  size_t ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREAD ; 
 int /*<<< orphan*/  IO_NODELOCKED ; 
 int /*<<< orphan*/  M_VERIEXEC ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NOCRED ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int VOP_GETATTR (int /*<<< orphan*/ ,struct vattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_UNLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open_file (char*,struct nameidata*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ verify_digest (char*,size_t,unsigned char*) ; 
 int /*<<< orphan*/  vn_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int vn_rdwr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,TYPE_1__*) ; 

__attribute__((used)) static char*
read_manifest(char *path, unsigned char *digest)
{
	struct nameidata	nid;
	struct vattr		va;
	char			*data;
	ssize_t			bytes_read, resid;
	int			rc;

	data = NULL;
	bytes_read = 0;

	rc = open_file(path, &nid);
	if (rc != 0)
		goto fail;

	rc = VOP_GETATTR(nid.ni_vp, &va, curthread->td_ucred);
	if (rc != 0)
		goto fail;

	data = (char *)malloc(va.va_size + 1, M_VERIEXEC, M_WAITOK);

	while (bytes_read < va.va_size) {
		rc = vn_rdwr(
		    UIO_READ, nid.ni_vp, data,
		    va.va_size - bytes_read, bytes_read,
		    UIO_SYSSPACE, IO_NODELOCKED,
		    curthread->td_ucred, NOCRED, &resid, curthread);
		if (rc != 0)
			goto fail;

		bytes_read = va.va_size - resid;
	}

	data[bytes_read] = '\0';

	VOP_UNLOCK(nid.ni_vp, 0);
	(void)vn_close(nid.ni_vp, FREAD, curthread->td_ucred, curthread);

	/*
	 * If digest is wrong someone might be trying to fool us.
	 */
	if (verify_digest(data, va.va_size, digest))
		panic("Manifest hash doesn't match expected value!");

	return (data);

fail:
	if (data != NULL)
		free(data, M_VERIEXEC);

	return (NULL);
}