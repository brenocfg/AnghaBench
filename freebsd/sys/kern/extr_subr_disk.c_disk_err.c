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
struct bio {int bio_cmd; int bio_bcount; scalar_t__ bio_pblkno; TYPE_1__* bio_disk; int /*<<< orphan*/ * bio_dev; } ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  scalar_t__ daddr_t ;
struct TYPE_2__ {char* d_name; char* d_unit; } ;

/* Variables and functions */
#define  BIO_DELETE 132 
#define  BIO_FLUSH 131 
#define  BIO_GETATTR 130 
#define  BIO_READ 129 
#define  BIO_WRITE 128 
 int DEV_BSIZE ; 
 char* devtoname (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
disk_err(struct bio *bp, const char *what, int blkdone, int nl)
{
	daddr_t sn;

	if (bp->bio_dev != NULL)
		printf("%s: %s ", devtoname(bp->bio_dev), what);
	else if (bp->bio_disk != NULL)
		printf("%s%d: %s ",
		    bp->bio_disk->d_name, bp->bio_disk->d_unit, what);
	else
		printf("disk??: %s ", what);
	switch(bp->bio_cmd) {
	case BIO_READ:		printf("cmd=read "); break;
	case BIO_WRITE:		printf("cmd=write "); break;
	case BIO_DELETE:	printf("cmd=delete "); break;
	case BIO_GETATTR:	printf("cmd=getattr "); break;
	case BIO_FLUSH:		printf("cmd=flush "); break;
	default:		printf("cmd=%x ", bp->bio_cmd); break;
	}
	sn = bp->bio_pblkno;
	if (bp->bio_bcount <= DEV_BSIZE) {
		printf("fsbn %jd%s", (intmax_t)sn, nl ? "\n" : "");
		return;
	}
	if (blkdone >= 0) {
		sn += blkdone;
		printf("fsbn %jd of ", (intmax_t)sn);
	}
	printf("%jd-%jd", (intmax_t)bp->bio_pblkno,
	    (intmax_t)(bp->bio_pblkno + (bp->bio_bcount - 1) / DEV_BSIZE));
	if (nl)
		printf("\n");
}