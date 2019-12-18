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
struct uio {int uio_resid; } ;
struct dirent {int d_namlen; int d_type; TYPE_1__* d_name; int /*<<< orphan*/  d_fileno; } ;
struct TYPE_3__ {int d_namlen; void* d_type; int /*<<< orphan*/  d_ino; int /*<<< orphan*/  d_next; } ;
typedef  TYPE_1__ cloudabi_dirent_t ;
typedef  int /*<<< orphan*/  cloudabi_dircookie_t ;
typedef  int /*<<< orphan*/  cde ;

/* Variables and functions */
 void* CLOUDABI_FILETYPE_BLOCK_DEVICE ; 
 void* CLOUDABI_FILETYPE_CHARACTER_DEVICE ; 
 void* CLOUDABI_FILETYPE_DIRECTORY ; 
 void* CLOUDABI_FILETYPE_REGULAR_FILE ; 
 void* CLOUDABI_FILETYPE_SOCKET_STREAM ; 
 void* CLOUDABI_FILETYPE_SYMBOLIC_LINK ; 
 void* CLOUDABI_FILETYPE_UNKNOWN ; 
#define  DT_BLK 134 
#define  DT_CHR 133 
#define  DT_DIR 132 
#define  DT_FIFO 131 
#define  DT_LNK 130 
#define  DT_REG 129 
#define  DT_SOCK 128 
 int uiomove (TYPE_1__*,size_t,struct uio*) ; 

__attribute__((used)) static int
write_dirent(struct dirent *bde, cloudabi_dircookie_t cookie, struct uio *uio)
{
	cloudabi_dirent_t cde = {
		.d_next = cookie,
		.d_ino = bde->d_fileno,
		.d_namlen = bde->d_namlen,
	};
	size_t len;
	int error;

	/* Convert file type. */
	switch (bde->d_type) {
	case DT_BLK:
		cde.d_type = CLOUDABI_FILETYPE_BLOCK_DEVICE;
		break;
	case DT_CHR:
		cde.d_type = CLOUDABI_FILETYPE_CHARACTER_DEVICE;
		break;
	case DT_DIR:
		cde.d_type = CLOUDABI_FILETYPE_DIRECTORY;
		break;
	case DT_FIFO:
		cde.d_type = CLOUDABI_FILETYPE_SOCKET_STREAM;
		break;
	case DT_LNK:
		cde.d_type = CLOUDABI_FILETYPE_SYMBOLIC_LINK;
		break;
	case DT_REG:
		cde.d_type = CLOUDABI_FILETYPE_REGULAR_FILE;
		break;
	case DT_SOCK:
		/* The exact socket type cannot be derived. */
		cde.d_type = CLOUDABI_FILETYPE_SOCKET_STREAM;
		break;
	default:
		cde.d_type = CLOUDABI_FILETYPE_UNKNOWN;
		break;
	}

	/* Write directory entry structure. */
	len = sizeof(cde) < uio->uio_resid ? sizeof(cde) : uio->uio_resid;
	error = uiomove(&cde, len, uio);
	if (error != 0)
		return (error);

	/* Write filename. */
	len = bde->d_namlen < uio->uio_resid ? bde->d_namlen : uio->uio_resid;
	return (uiomove(bde->d_name, len, uio));
}