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
typedef  int u_int32_t ;
struct partition {long p_size; long p_offset; int p_fsize; long p_frag; int p_fstype; } ;
struct disklabel {char* d_typename; int d_secsize; int d_ntracks; int d_nsectors; int d_ncylinders; int d_type; int d_secpercyl; int d_secperunit; int d_rpm; int d_interleave; int d_trackskew; int d_cylskew; int d_headswitch; int d_trkseek; int d_bbsize; int d_sbsize; char d_npartitions; int* d_drivedata; void* d_magic2; void* d_magic; struct partition* d_partitions; int /*<<< orphan*/  d_flags; } ;
typedef  int /*<<< orphan*/  disk ;

/* Variables and functions */
 int BBSIZE ; 
 int DEV_BSIZE ; 
 void* DISKMAGIC ; 
 int /*<<< orphan*/  D_BADSECT ; 
 int /*<<< orphan*/  D_RAMDISK ; 
 int /*<<< orphan*/  D_REMOVABLE ; 
 char MAXPARTITIONS ; 
 char NDDATA ; 
 char* _PATH_DISKTAB ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/ * cgetcap (char*,char*,char) ; 
 scalar_t__ cgetent (char**,char**,char*) ; 
 scalar_t__ cgetnum (char*,char*,long*) ; 
 scalar_t__ cgetstr (char*,char*,char**) ; 
 int /*<<< orphan*/  dktypenames ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fstypenames ; 
 int /*<<< orphan*/  getnumdflt (int,char*,int) ; 
 void* gettype (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

struct disklabel *
getdiskbyname(const char *name)
{
	static struct	disklabel disk;
	struct	disklabel *dp = &disk;
	struct partition *pp;
	char	*buf;
	char  	*db_array[2] = { _PATH_DISKTAB, 0 };
	char	*cp, *cq;	/* can't be register */
	char	p, max, psize[3], pbsize[3],
		pfsize[3], poffset[3], ptype[3];
	u_int32_t *dx;

	if (cgetent(&buf, db_array, (char *) name) < 0)
		return NULL;

	bzero((char *)&disk, sizeof(disk));
	/*
	 * typename
	 */
	cq = dp->d_typename;
	cp = buf;
	while (cq < dp->d_typename + sizeof(dp->d_typename) - 1 &&
	    (*cq = *cp) && *cq != '|' && *cq != ':')
		cq++, cp++;
	*cq = '\0';

	if (cgetstr(buf, "ty", &cq) > 0) {
		if (strcmp(cq, "removable") == 0)
			dp->d_flags |= D_REMOVABLE;
		else  if (cq && strcmp(cq, "simulated") == 0)
			dp->d_flags |= D_RAMDISK;
		free(cq);
	}
	if (cgetcap(buf, "sf", ':') != NULL)
		dp->d_flags |= D_BADSECT;

#define getnumdflt(field, dname, dflt) \
        { long f; (field) = (cgetnum(buf, dname, &f) == -1) ? (dflt) : f; }

	getnumdflt(dp->d_secsize, "se", DEV_BSIZE);
	getnumdflt(dp->d_ntracks, "nt", 0);
	getnumdflt(dp->d_nsectors, "ns", 0);
	getnumdflt(dp->d_ncylinders, "nc", 0);

	if (cgetstr(buf, "dt", &cq) > 0) {
		dp->d_type = gettype(cq, dktypenames);
		free(cq);
	} else
		getnumdflt(dp->d_type, "dt", 0);
	getnumdflt(dp->d_secpercyl, "sc", dp->d_nsectors * dp->d_ntracks);
	getnumdflt(dp->d_secperunit, "su", dp->d_secpercyl * dp->d_ncylinders);
	getnumdflt(dp->d_rpm, "rm", 3600);
	getnumdflt(dp->d_interleave, "il", 1);
	getnumdflt(dp->d_trackskew, "sk", 0);
	getnumdflt(dp->d_cylskew, "cs", 0);
	getnumdflt(dp->d_headswitch, "hs", 0);
	getnumdflt(dp->d_trkseek, "ts", 0);
	getnumdflt(dp->d_bbsize, "bs", BBSIZE);
	getnumdflt(dp->d_sbsize, "sb", 0);
	strcpy(psize, "px");
	strcpy(pbsize, "bx");
	strcpy(pfsize, "fx");
	strcpy(poffset, "ox");
	strcpy(ptype, "tx");
	max = 'a' - 1;
	pp = &dp->d_partitions[0];
	for (p = 'a'; p < 'a' + MAXPARTITIONS; p++, pp++) {
		long l;
		psize[1] = pbsize[1] = pfsize[1] = poffset[1] = ptype[1] = p;
		if (cgetnum(buf, psize, &l) == -1)
			pp->p_size = 0;
		else {
			pp->p_size = l;
			cgetnum(buf, poffset, &l);
			pp->p_offset = l;
			getnumdflt(pp->p_fsize, pfsize, 0);
			if (pp->p_fsize) {
				long bsize;

				if (cgetnum(buf, pbsize, &bsize) == 0)
					pp->p_frag = bsize / pp->p_fsize;
				else
					pp->p_frag = 8;
			}
			getnumdflt(pp->p_fstype, ptype, 0);
			if (pp->p_fstype == 0)
				if (cgetstr(buf, ptype, &cq) >= 0) {
					pp->p_fstype = gettype(cq, fstypenames);
					free(cq);
				}
			max = p;
		}
	}
	dp->d_npartitions = max + 1 - 'a';
	(void)strcpy(psize, "dx");
	dx = dp->d_drivedata;
	for (p = '0'; p < '0' + NDDATA; p++, dx++) {
		psize[1] = p;
		getnumdflt(*dx, psize, 0);
	}
	dp->d_magic = DISKMAGIC;
	dp->d_magic2 = DISKMAGIC;
	free(buf);
	return (dp);
}