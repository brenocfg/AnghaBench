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
typedef  int uintmax_t ;
typedef  scalar_t__ u_char ;
typedef  scalar_t__ saidx_t ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BZFILE ;

/* Variables and functions */
 int /*<<< orphan*/  BZ2_bzWrite (int*,int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  BZ2_bzWriteClose (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BZ2_bzWriteOpen (int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BZ_OK ; 
 int /*<<< orphan*/  EFBIG ; 
 int OFF_MAX ; 
 int O_BINARY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SIZE_T_MAX ; 
 int SSIZE_MAX ; 
 int close (int) ; 
 scalar_t__ divsufsort (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__ fseeko (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ftello (int /*<<< orphan*/ *) ; 
 int fwrite (scalar_t__*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char*,int) ; 
 int /*<<< orphan*/  offtout (int,scalar_t__*) ; 
 int open (char*,int,int /*<<< orphan*/ ) ; 
 int read (int,scalar_t__*,int) ; 
 int search (scalar_t__*,scalar_t__*,int,scalar_t__*,int,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc,char *argv[])
{
	int fd;
	u_char *old,*new;
	off_t oldsize,newsize;
	saidx_t *I;
	off_t scan,pos,len;
	off_t lastscan,lastpos,lastoffset;
	off_t oldscore,scsc;
	off_t s,Sf,lenf,Sb,lenb;
	off_t overlap,Ss,lens;
	off_t i;
	off_t dblen,eblen;
	u_char *db,*eb;
	u_char buf[8];
	u_char header[32];
	FILE * pf;
	BZFILE * pfbz2;
	int bz2err;

	if (argc != 4)
		usage();

	/* Allocate oldsize+1 bytes instead of oldsize bytes to ensure
		that we never try to malloc(0) and get a NULL pointer */
	if(((fd=open(argv[1],O_RDONLY|O_BINARY,0))<0) ||
	    ((oldsize=lseek(fd,0,SEEK_END))==-1))
		err(1, "%s", argv[1]);

	if (oldsize > SSIZE_MAX ||
	    (uintmax_t)oldsize >= SIZE_T_MAX / sizeof(off_t) ||
	    oldsize == OFF_MAX) {
		errno = EFBIG;
		err(1, "%s", argv[1]);
	}

	if (((old=malloc(oldsize+1))==NULL) ||
		(lseek(fd,0,SEEK_SET)!=0) ||
		(read(fd,old,oldsize)!=oldsize) ||
		(close(fd)==-1)) err(1,"%s",argv[1]);

	if(((I=malloc((oldsize+1)*sizeof(saidx_t)))==NULL)) err(1,NULL);

	if(divsufsort(old, I, oldsize)) err(1, "divsufsort");

	/* Allocate newsize+1 bytes instead of newsize bytes to ensure
		that we never try to malloc(0) and get a NULL pointer */
	if(((fd=open(argv[2],O_RDONLY|O_BINARY,0))<0) ||
	    ((newsize=lseek(fd,0,SEEK_END))==-1))
		err(1, "%s", argv[2]);

	if (newsize > SSIZE_MAX || (uintmax_t)newsize >= SIZE_T_MAX ||
	    newsize == OFF_MAX) {
		errno = EFBIG;
		err(1, "%s", argv[2]);
	}

	if (((new=malloc(newsize+1))==NULL) ||
		(lseek(fd,0,SEEK_SET)!=0) ||
		(read(fd,new,newsize)!=newsize) ||
		(close(fd)==-1)) err(1,"%s",argv[2]);

	if(((db=malloc(newsize+1))==NULL) ||
		((eb=malloc(newsize+1))==NULL)) err(1,NULL);
	dblen=0;
	eblen=0;

	/* Create the patch file */
	if ((pf = fopen(argv[3], "wb")) == NULL)
		err(1, "%s", argv[3]);

	/* Header is
		0	8	 "BSDIFF40"
		8	8	length of bzip2ed ctrl block
		16	8	length of bzip2ed diff block
		24	8	length of new file */
	/* File is
		0	32	Header
		32	??	Bzip2ed ctrl block
		??	??	Bzip2ed diff block
		??	??	Bzip2ed extra block */
	memcpy(header,"BSDIFF40",8);
	offtout(0, header + 8);
	offtout(0, header + 16);
	offtout(newsize, header + 24);
	if (fwrite(header, 32, 1, pf) != 1)
		err(1, "fwrite(%s)", argv[3]);

	/* Compute the differences, writing ctrl as we go */
	if ((pfbz2 = BZ2_bzWriteOpen(&bz2err, pf, 9, 0, 0)) == NULL)
		errx(1, "BZ2_bzWriteOpen, bz2err = %d", bz2err);
	scan=0;len=0;pos=0;
	lastscan=0;lastpos=0;lastoffset=0;
	while(scan<newsize) {
		oldscore=0;

		for(scsc=scan+=len;scan<newsize;scan++) {
			len=search(I,old,oldsize,new+scan,newsize-scan,
					0,oldsize,&pos);

			for(;scsc<scan+len;scsc++)
			if((scsc+lastoffset<oldsize) &&
				(old[scsc+lastoffset] == new[scsc]))
				oldscore++;

			if(((len==oldscore) && (len!=0)) || 
				(len>oldscore+8)) break;

			if((scan+lastoffset<oldsize) &&
				(old[scan+lastoffset] == new[scan]))
				oldscore--;
		}

		if((len!=oldscore) || (scan==newsize)) {
			s=0;Sf=0;lenf=0;
			for(i=0;(lastscan+i<scan)&&(lastpos+i<oldsize);) {
				if(old[lastpos+i]==new[lastscan+i]) s++;
				i++;
				if(s*2-i>Sf*2-lenf) { Sf=s; lenf=i; }
			}

			lenb=0;
			if(scan<newsize) {
				s=0;Sb=0;
				for(i=1;(scan>=lastscan+i)&&(pos>=i);i++) {
					if(old[pos-i]==new[scan-i]) s++;
					if(s*2-i>Sb*2-lenb) { Sb=s; lenb=i; }
				}
			}

			if(lastscan+lenf>scan-lenb) {
				overlap=(lastscan+lenf)-(scan-lenb);
				s=0;Ss=0;lens=0;
				for(i=0;i<overlap;i++) {
					if(new[lastscan+lenf-overlap+i]==
					   old[lastpos+lenf-overlap+i]) s++;
					if(new[scan-lenb+i]==
					   old[pos-lenb+i]) s--;
					if(s>Ss) { Ss=s; lens=i+1; }
				}

				lenf+=lens-overlap;
				lenb-=lens;
			}

			for(i=0;i<lenf;i++)
				db[dblen+i]=new[lastscan+i]-old[lastpos+i];
			for(i=0;i<(scan-lenb)-(lastscan+lenf);i++)
				eb[eblen+i]=new[lastscan+lenf+i];

			dblen+=lenf;
			eblen+=(scan-lenb)-(lastscan+lenf);

			offtout(lenf,buf);
			BZ2_bzWrite(&bz2err, pfbz2, buf, 8);
			if (bz2err != BZ_OK)
				errx(1, "BZ2_bzWrite, bz2err = %d", bz2err);

			offtout((scan-lenb)-(lastscan+lenf),buf);
			BZ2_bzWrite(&bz2err, pfbz2, buf, 8);
			if (bz2err != BZ_OK)
				errx(1, "BZ2_bzWrite, bz2err = %d", bz2err);

			offtout((pos-lenb)-(lastpos+lenf),buf);
			BZ2_bzWrite(&bz2err, pfbz2, buf, 8);
			if (bz2err != BZ_OK)
				errx(1, "BZ2_bzWrite, bz2err = %d", bz2err);

			lastscan=scan-lenb;
			lastpos=pos-lenb;
			lastoffset=pos-scan;
		}
	}
	BZ2_bzWriteClose(&bz2err, pfbz2, 0, NULL, NULL);
	if (bz2err != BZ_OK)
		errx(1, "BZ2_bzWriteClose, bz2err = %d", bz2err);

	/* Compute size of compressed ctrl data */
	if ((len = ftello(pf)) == -1)
		err(1, "ftello");
	offtout(len-32, header + 8);

	/* Write compressed diff data */
	if ((pfbz2 = BZ2_bzWriteOpen(&bz2err, pf, 9, 0, 0)) == NULL)
		errx(1, "BZ2_bzWriteOpen, bz2err = %d", bz2err);
	BZ2_bzWrite(&bz2err, pfbz2, db, dblen);
	if (bz2err != BZ_OK)
		errx(1, "BZ2_bzWrite, bz2err = %d", bz2err);
	BZ2_bzWriteClose(&bz2err, pfbz2, 0, NULL, NULL);
	if (bz2err != BZ_OK)
		errx(1, "BZ2_bzWriteClose, bz2err = %d", bz2err);

	/* Compute size of compressed diff data */
	if ((newsize = ftello(pf)) == -1)
		err(1, "ftello");
	offtout(newsize - len, header + 16);

	/* Write compressed extra data */
	if ((pfbz2 = BZ2_bzWriteOpen(&bz2err, pf, 9, 0, 0)) == NULL)
		errx(1, "BZ2_bzWriteOpen, bz2err = %d", bz2err);
	BZ2_bzWrite(&bz2err, pfbz2, eb, eblen);
	if (bz2err != BZ_OK)
		errx(1, "BZ2_bzWrite, bz2err = %d", bz2err);
	BZ2_bzWriteClose(&bz2err, pfbz2, 0, NULL, NULL);
	if (bz2err != BZ_OK)
		errx(1, "BZ2_bzWriteClose, bz2err = %d", bz2err);

	/* Seek to the beginning, write the header, and close the file */
	if (fseeko(pf, 0, SEEK_SET))
		err(1, "fseeko");
	if (fwrite(header, 32, 1, pf) != 1)
		err(1, "fwrite(%s)", argv[3]);
	if (fclose(pf))
		err(1, "fclose");

	/* Free the memory we used */
	free(db);
	free(eb);
	free(I);
	free(old);
	free(new);

	return 0;
}