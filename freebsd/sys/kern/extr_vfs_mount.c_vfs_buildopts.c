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
struct vfsoptlist {int dummy; } ;
struct vfsopt {char* name; char* value; size_t len; unsigned int pos; scalar_t__ seen; } ;
struct uio {unsigned int uio_iovcnt; scalar_t__ uio_segflg; TYPE_1__* uio_iov; } ;
struct TYPE_2__ {size_t iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  M_MOUNT ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  TAILQ_INIT (struct vfsoptlist*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct vfsoptlist*,struct vfsopt*,int /*<<< orphan*/ ) ; 
 scalar_t__ UIO_SYSSPACE ; 
 size_t VFS_MOUNTARG_SIZE_MAX ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,char*,size_t) ; 
 int copyin (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  link ; 
 void* malloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_freeopts (struct vfsoptlist*) ; 
 int /*<<< orphan*/  vfs_sanitizeopts (struct vfsoptlist*) ; 

int
vfs_buildopts(struct uio *auio, struct vfsoptlist **options)
{
	struct vfsoptlist *opts;
	struct vfsopt *opt;
	size_t memused, namelen, optlen;
	unsigned int i, iovcnt;
	int error;

	opts = malloc(sizeof(struct vfsoptlist), M_MOUNT, M_WAITOK);
	TAILQ_INIT(opts);
	memused = 0;
	iovcnt = auio->uio_iovcnt;
	for (i = 0; i < iovcnt; i += 2) {
		namelen = auio->uio_iov[i].iov_len;
		optlen = auio->uio_iov[i + 1].iov_len;
		memused += sizeof(struct vfsopt) + optlen + namelen;
		/*
		 * Avoid consuming too much memory, and attempts to overflow
		 * memused.
		 */
		if (memused > VFS_MOUNTARG_SIZE_MAX ||
		    optlen > VFS_MOUNTARG_SIZE_MAX ||
		    namelen > VFS_MOUNTARG_SIZE_MAX) {
			error = EINVAL;
			goto bad;
		}

		opt = malloc(sizeof(struct vfsopt), M_MOUNT, M_WAITOK);
		opt->name = malloc(namelen, M_MOUNT, M_WAITOK);
		opt->value = NULL;
		opt->len = 0;
		opt->pos = i / 2;
		opt->seen = 0;

		/*
		 * Do this early, so jumps to "bad" will free the current
		 * option.
		 */
		TAILQ_INSERT_TAIL(opts, opt, link);

		if (auio->uio_segflg == UIO_SYSSPACE) {
			bcopy(auio->uio_iov[i].iov_base, opt->name, namelen);
		} else {
			error = copyin(auio->uio_iov[i].iov_base, opt->name,
			    namelen);
			if (error)
				goto bad;
		}
		/* Ensure names are null-terminated strings. */
		if (namelen == 0 || opt->name[namelen - 1] != '\0') {
			error = EINVAL;
			goto bad;
		}
		if (optlen != 0) {
			opt->len = optlen;
			opt->value = malloc(optlen, M_MOUNT, M_WAITOK);
			if (auio->uio_segflg == UIO_SYSSPACE) {
				bcopy(auio->uio_iov[i + 1].iov_base, opt->value,
				    optlen);
			} else {
				error = copyin(auio->uio_iov[i + 1].iov_base,
				    opt->value, optlen);
				if (error)
					goto bad;
			}
		}
	}
	vfs_sanitizeopts(opts);
	*options = opts;
	return (0);
bad:
	vfs_freeopts(opts);
	return (error);
}