#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct open_file {int dummy; } ;
struct dirent {int d_fileno; int d_reclen; int /*<<< orphan*/  d_name; int /*<<< orphan*/  d_type; } ;
typedef  int /*<<< orphan*/  dd ;
struct TYPE_7__ {int* name; int attr; int* clus; int /*<<< orphan*/  ext; } ;
struct TYPE_6__ {int seq; int chk; } ;
struct TYPE_5__ {TYPE_4__ de; TYPE_3__ xde; } ;
typedef  TYPE_1__ DOS_DIR ;

/* Variables and functions */
 int /*<<< orphan*/  DT_DIR ; 
 int /*<<< orphan*/  DT_REG ; 
 int ENOENT ; 
 int FA_DIR ; 
 int FA_LABEL ; 
 int FA_MASK ; 
 int FA_XDE ; 
 int /*<<< orphan*/  cp_sfn (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  cp_xdnm (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int dos_checksum (int*,int /*<<< orphan*/ ) ; 
 int dos_read (struct open_file*,TYPE_1__*,int,size_t*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
dos_readdir(struct open_file *fd, struct dirent *d)
{
    /* DOS_FILE *f = (DOS_FILE *)fd->f_fsdata; */
    u_char fn[261];
    DOS_DIR dd;
    size_t res;
    u_int chk, x, xdn;
    int err;

    x = chk = 0;
    while (1) {
	xdn = x;
	x = 0;
	err = dos_read(fd, &dd, sizeof(dd), &res);
	if (err)
	    return (err);
	if (res == sizeof(dd))
	    return (ENOENT);
	if (dd.de.name[0] == 0)
	    return (ENOENT);

	/* Skip deleted entries */
	if (dd.de.name[0] == 0xe5)
	    continue;

	/* Check if directory entry is volume label */
	if (dd.de.attr & FA_LABEL) {
	    /* 
	     * If volume label set, check if the current entry is
	     * extended entry (FA_XDE) for long file names.
	     */
	    if ((dd.de.attr & FA_MASK) == FA_XDE) {
		/*
		 * Read through all following extended entries
		 * to get the long file name. 0x40 marks the
		 * last entry containing part of long file name.
		 */
		if (dd.xde.seq & 0x40)
		    chk = dd.xde.chk;
		else if (dd.xde.seq != xdn - 1 || dd.xde.chk != chk)
		    continue;
		x = dd.xde.seq & ~0x40;
		if (x < 1 || x > 20) {
		    x = 0;
		    continue;
		}
		cp_xdnm(fn, &dd.xde);
	    } else {
		/* skip only volume label entries */
		continue;
	    }
	} else {
	    if (xdn == 1) {
		x = dos_checksum(dd.de.name, dd.de.ext);
		if (x == chk)
		    break;
	    } else {
		cp_sfn(fn, &dd.de);
		break;
	    }
	    x = 0;
	}
    }

    d->d_fileno = (dd.de.clus[1] << 8) + dd.de.clus[0];
    d->d_reclen = sizeof(*d);
    d->d_type = (dd.de.attr & FA_DIR) ? DT_DIR : DT_REG;
    memcpy(d->d_name, fn, sizeof(d->d_name));
    return (0);
}