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
struct open_file {scalar_t__ f_fsdata; } ;
struct iso_directory_record {char* name; int /*<<< orphan*/  length; int /*<<< orphan*/  flags; int /*<<< orphan*/  extent; int /*<<< orphan*/  name_len; } ;
struct file {int f_off; int f_size; int f_flags; int f_susp_skip; } ;
struct dirent {size_t d_reclen; size_t d_namlen; scalar_t__* d_name; int /*<<< orphan*/  d_type; int /*<<< orphan*/  d_fileno; } ;
typedef  int daddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DT_DIR ; 
 int /*<<< orphan*/  DT_REG ; 
 int ENOENT ; 
 int F_ROOTDIR ; 
 int F_RR ; 
 int ISO_DEFAULT_BLOCK_SIZE ; 
 int MAXNAMLEN ; 
 int /*<<< orphan*/  bcopy (char*,scalar_t__*,size_t) ; 
 int buf_read_file (struct open_file*,char**,size_t*) ; 
 int isonum_711 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isonum_733 (int /*<<< orphan*/ ) ; 
 char* rrip_lookup_name (struct open_file*,struct iso_directory_record*,int,size_t*) ; 

__attribute__((used)) static int
cd9660_readdir(struct open_file *f, struct dirent *d)
{
	struct file *fp = (struct file *)f->f_fsdata;
	struct iso_directory_record *ep;
	size_t buf_size, reclen, namelen;
	int error = 0;
	int lenskip;
	char *buf, *name;

again:
	if (fp->f_off >= fp->f_size)
		return (ENOENT);
	error = buf_read_file(f, &buf, &buf_size);
	if (error)
		return (error);
	ep = (struct iso_directory_record *)buf;

	if (isonum_711(ep->length) == 0) {
		daddr_t blkno;
		
		/* skip to next block, if any */
		blkno = fp->f_off / ISO_DEFAULT_BLOCK_SIZE;
		fp->f_off = (blkno + 1) * ISO_DEFAULT_BLOCK_SIZE;
		goto again;
	}

	if (fp->f_flags & F_RR) {
		if (fp->f_flags & F_ROOTDIR && fp->f_off == 0)
			lenskip = 0;
		else
			lenskip = fp->f_susp_skip;
		name = rrip_lookup_name(f, ep, lenskip, &namelen);
	} else
		name = NULL;
	if (name == NULL) {
		namelen = isonum_711(ep->name_len);
		name = ep->name;
		if (namelen == 1) {
			if (ep->name[0] == 0)
				name = ".";
			else if (ep->name[0] == 1) {
				namelen = 2;
				name = "..";
			}
		}
	}
	reclen = sizeof(struct dirent) - (MAXNAMLEN+1) + namelen + 1;
	reclen = (reclen + 3) & ~3;

	d->d_fileno = isonum_733(ep->extent);
	d->d_reclen = reclen;
	if (isonum_711(ep->flags) & 2)
		d->d_type = DT_DIR;
	else
		d->d_type = DT_REG;
	d->d_namlen = namelen;

	bcopy(name, d->d_name, d->d_namlen);
	d->d_name[d->d_namlen] = 0;

	fp->f_off += isonum_711(ep->length);
	return (0);
}