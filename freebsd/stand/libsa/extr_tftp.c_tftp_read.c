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
struct tftp_handle {scalar_t__ tftp_tsize; size_t off; int tftp_blksize; int currblock; int validsize; scalar_t__ islastblock; TYPE_1__* tftp_hdr; } ;
struct open_file {struct tftp_handle* f_fsdata; } ;
struct TYPE_2__ {scalar_t__ th_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bcopy (scalar_t__,void*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int tftp_getnextblock (struct tftp_handle*) ; 
 int tftp_makereq (struct tftp_handle*) ; 
 int /*<<< orphan*/  tftp_senderr (struct tftp_handle*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  twiddle (int) ; 

__attribute__((used)) static int
tftp_read(struct open_file *f, void *addr, size_t size,
    size_t *resid /* out */)
{
	struct tftp_handle *tftpfile;
	size_t res;
	int rc;

	rc = 0;
	res = size;
	tftpfile = f->f_fsdata;

	/* Make sure we will not read past file end */
	if (tftpfile->tftp_tsize > 0 &&
	    tftpfile->off + size > tftpfile->tftp_tsize) {
		size = tftpfile->tftp_tsize - tftpfile->off;
	}

	while (size > 0) {
		int needblock, count;

		twiddle(32);

		needblock = tftpfile->off / tftpfile->tftp_blksize + 1;

		if (tftpfile->currblock > needblock) {	/* seek backwards */
			tftp_senderr(tftpfile, 0, "No error: read aborted");
			rc = tftp_makereq(tftpfile);
			if (rc != 0)
				break;
		}

		while (tftpfile->currblock < needblock) {

			rc = tftp_getnextblock(tftpfile);
			if (rc) {	/* no answer */
#ifdef TFTP_DEBUG
				printf("tftp: read error\n");
#endif
				return (rc);
			}
			if (tftpfile->islastblock)
				break;
		}

		if (tftpfile->currblock == needblock) {
			int offinblock, inbuffer;

			offinblock = tftpfile->off % tftpfile->tftp_blksize;

			inbuffer = tftpfile->validsize - offinblock;
			if (inbuffer < 0) {
#ifdef TFTP_DEBUG
				printf("tftp: invalid offset %d\n",
				    tftpfile->off);
#endif
				return (EINVAL);
			}
			count = (size < inbuffer ? size : inbuffer);
			bcopy(tftpfile->tftp_hdr->th_data + offinblock,
			    addr, count);

			addr = (char *)addr + count;
			tftpfile->off += count;
			size -= count;
			res -= count;

			if ((tftpfile->islastblock) && (count == inbuffer))
				break;	/* EOF */
		} else {
#ifdef TFTP_DEBUG
			printf("tftp: block %d not found\n", needblock);
#endif
			return (EINVAL);
		}

	}

	if (resid != NULL)
		*resid = res;
	return (rc);
}