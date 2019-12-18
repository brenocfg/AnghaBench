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
typedef  int /*<<< orphan*/  u_char ;
struct s_spcl {scalar_t__ c_magic; int c_flags; int c_type; int c_size; int c_count; int /*<<< orphan*/  c_tapea; int /*<<< orphan*/ * c_spare1; int /*<<< orphan*/  c_gid; int /*<<< orphan*/  c_uid; void* c_date; int /*<<< orphan*/  c_extsize; int /*<<< orphan*/  c_birthtimensec; int /*<<< orphan*/  c_birthtime; int /*<<< orphan*/  c_old_mtime; void* c_mtime; int /*<<< orphan*/  c_old_atime; void* c_atime; int /*<<< orphan*/  c_old_ddate; void* c_ddate; int /*<<< orphan*/  c_old_date; int /*<<< orphan*/  c_old_firstrec; int /*<<< orphan*/  c_firstrec; int /*<<< orphan*/  c_old_tapea; int /*<<< orphan*/  c_inumber; int /*<<< orphan*/ * c_addr; int /*<<< orphan*/  c_level; } ;

/* Variables and functions */
 int Bcvt ; 
 int FAIL ; 
 scalar_t__ FS_UFS2_MAGIC ; 
 int GOOD ; 
 int NFS_DR_NEWINODEFMT ; 
 scalar_t__ NFS_MAGIC ; 
 scalar_t__ OFS_MAGIC ; 
 int TP_BSIZE ; 
 int TP_NINDIR ; 
#define  TS_ADDR 133 
#define  TS_BITS 132 
#define  TS_CLRI 131 
#define  TS_END 130 
#define  TS_INODE 129 
#define  TS_TAPE 128 
 void* _time32_to_time (int /*<<< orphan*/ ) ; 
 scalar_t__ _time64_to_time (void*) ; 
 int /*<<< orphan*/  accthdr (struct s_spcl*) ; 
 int checksum (int*) ; 
 scalar_t__ dflag ; 
 scalar_t__ dumpdate ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int oldinofmt ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int readmapflag ; 
 int /*<<< orphan*/  readtape (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ swabl (scalar_t__) ; 
 int /*<<< orphan*/  swabst (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tapeaddr ; 
 int /*<<< orphan*/  vprintf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
gethead(struct s_spcl *buf)
{
	long i;

	readtape((char *)buf);
	if (buf->c_magic != FS_UFS2_MAGIC && buf->c_magic != NFS_MAGIC) {
		if (buf->c_magic == OFS_MAGIC) {
			fprintf(stderr,
			    "Format of dump tape is too old. Must use\n");
			fprintf(stderr,
			    "a version of restore from before 2002.\n");
			return (FAIL);
		}
		if (swabl(buf->c_magic) != FS_UFS2_MAGIC &&
		    swabl(buf->c_magic) != NFS_MAGIC) {
			if (swabl(buf->c_magic) == OFS_MAGIC) {
				fprintf(stderr,
				  "Format of dump tape is too old. Must use\n");
				fprintf(stderr,
				  "a version of restore from before 2002.\n");
			}
			return (FAIL);
		}
		if (!Bcvt) {
			vprintf(stdout, "Note: Doing Byte swapping\n");
			Bcvt = 1;
		}
	}
	if (checksum((int *)buf) == FAIL)
		return (FAIL);
	if (Bcvt) {
		swabst((u_char *)"8l4s1q8l2q17l", (u_char *)buf);
		swabst((u_char *)"l",(u_char *) &buf->c_level);
		swabst((u_char *)"2l4q",(u_char *) &buf->c_flags);
	}
	readmapflag = 0;

	switch (buf->c_type) {

	case TS_CLRI:
	case TS_BITS:
		/*
		 * Have to patch up missing information in bit map headers
		 */
		buf->c_size = buf->c_count * TP_BSIZE;
		if (buf->c_count > TP_NINDIR)
			readmapflag = 1;
		else 
			for (i = 0; i < buf->c_count; i++)
				buf->c_addr[i]++;
		/* FALL THROUGH */

	case TS_TAPE:
		if (buf->c_magic == NFS_MAGIC &&
		    (buf->c_flags & NFS_DR_NEWINODEFMT) == 0)
			oldinofmt = 1;
		/* FALL THROUGH */

	case TS_END:
		buf->c_inumber = 0;
		/* FALL THROUGH */

	case TS_ADDR:
	case TS_INODE:
		/*
		 * For old dump tapes, have to copy up old fields to
		 * new locations.
		 */
		if (buf->c_magic == NFS_MAGIC) {
			buf->c_tapea = buf->c_old_tapea;
			buf->c_firstrec = buf->c_old_firstrec;
			buf->c_date = _time32_to_time(buf->c_old_date);
			buf->c_ddate = _time32_to_time(buf->c_old_ddate);
			buf->c_atime = _time32_to_time(buf->c_old_atime);
			buf->c_mtime = _time32_to_time(buf->c_old_mtime);
			buf->c_birthtime = 0;
			buf->c_birthtimensec = 0;
			buf->c_extsize = 0;
		}
		break;

	default:
		panic("gethead: unknown inode type %d\n", buf->c_type);
		break;
	}
	if (dumpdate != 0 && _time64_to_time(buf->c_date) != dumpdate)
		fprintf(stderr, "Header with wrong dumpdate.\n");
	/*
	 * If we're restoring a filesystem with the old (FreeBSD 1)
	 * format inodes, copy the uid/gid to the new location
	 */
	if (oldinofmt) {
		buf->c_uid = buf->c_spare1[1];
		buf->c_gid = buf->c_spare1[2];
	}
	buf->c_magic = FS_UFS2_MAGIC;
	tapeaddr = buf->c_tapea;
	if (dflag)
		accthdr(buf);
	return(GOOD);
}