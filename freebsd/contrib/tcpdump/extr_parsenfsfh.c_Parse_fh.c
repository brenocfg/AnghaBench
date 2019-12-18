#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  tempa ;
struct TYPE_4__ {unsigned char Minor; unsigned char Major; } ;
struct TYPE_5__ {char* Opaque_Handle; TYPE_1__ Fsid_dev; void* fsid_code; } ;
typedef  TYPE_2__ my_fsid ;

/* Variables and functions */
#define  FHT_AIX32 140 
#define  FHT_AUSPEX 139 
#define  FHT_BSD44 138 
#define  FHT_DECOSF 137 
#define  FHT_HPUX9 136 
#define  FHT_IRIX4 135 
#define  FHT_IRIX5 134 
#define  FHT_SUNOS3 133 
#define  FHT_SUNOS4 132 
#define  FHT_SUNOS5 131 
#define  FHT_ULTRIX 130 
#define  FHT_UNKNOWN 129 
#define  FHT_VMSUCX 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ is_UCX (unsigned char const*,int) ; 
 void* make_uint16 (unsigned char const,unsigned char const) ; 
 int make_uint24 (unsigned char const,unsigned char const,unsigned char const) ; 
 void* make_uint32 (unsigned char const,unsigned char const,unsigned char const,unsigned char const) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned char const) ; 
 int /*<<< orphan*/  stderr ; 

void
Parse_fh(register const unsigned char *fh, u_int len, my_fsid *fsidp,
	 uint32_t *inop,
	 const char **osnamep, /* if non-NULL, return OS name here */
	 const char **fsnamep, /* if non-NULL, return server fs name here (for VMS) */
	 int ourself)	/* true if file handle was generated on this host */
{
	register const unsigned char *fhp = fh;
	uint32_t temp;
	int fhtype = FHT_UNKNOWN;
	u_int i;

	/*
	 * Require at least 16 bytes of file handle; it's variable-length
	 * in NFSv3.  "len" is in units of 32-bit words, not bytes.
	 */
	if (len < 16/4)
		fhtype = FHT_UNKNOWN;
	else {
		if (ourself) {
		    /* File handle generated on this host, no need for guessing */
#if	defined(IRIX40)
		    fhtype = FHT_IRIX4;
#endif
#if	defined(IRIX50)
		    fhtype = FHT_IRIX5;
#endif
#if	defined(IRIX51)
		    fhtype = FHT_IRIX5;
#endif
#if	defined(SUNOS4)
		    fhtype = FHT_SUNOS4;
#endif
#if	defined(SUNOS5)
		    fhtype = FHT_SUNOS5;
#endif
#if	defined(ultrix)
		    fhtype = FHT_ULTRIX;
#endif
#if	defined(__osf__)
		    fhtype = FHT_DECOSF;
#endif
#if	defined(__NetBSD__) || defined(__FreeBSD__) || defined(__DragonFly__) \
     || defined(__OpenBSD__)
		    fhtype = FHT_BSD44;
#endif
		}
		/*
		 * This is basically a big decision tree
		 */
		else if ((fhp[0] == 0) && (fhp[1] == 0)) {
		    /* bytes[0,1] == (0,0); rules out Ultrix, IRIX5, SUNOS5 */
		    /* probably rules out HP-UX, AIX unless they allow major=0 */
		    if ((fhp[2] == 0) && (fhp[3] == 0)) {
			/* bytes[2,3] == (0,0); must be Auspex */
			/* XXX or could be Ultrix+MASSBUS "hp" disk? */
			fhtype = FHT_AUSPEX;
		    }
		    else {
			/*
			 * bytes[2,3] != (0,0); rules out Auspex, could be
			 * DECOSF, SUNOS4, or IRIX4
			 */
			if ((fhp[4] != 0) && (fhp[5] == 0) &&
				(fhp[8] == 12) && (fhp[9] == 0)) {
			    /* seems to be DECOSF, with minor == 0 */
			    fhtype = FHT_DECOSF;
			}
			else {
			    /* could be SUNOS4 or IRIX4 */
			    /* XXX the test of fhp[5] == 8 could be wrong */
			    if ((fhp[4] == 0) && (fhp[5] == 8) && (fhp[6] == 0) &&
			        (fhp[7] == 0)) {
				/* looks like a length, not a file system typecode */
				fhtype = FHT_IRIX4;
			    }
			    else {
				/* by elimination */
				fhtype = FHT_SUNOS4;
			    }
			}
		    }
		}
		else {
		    /*
		     * bytes[0,1] != (0,0); rules out Auspex, IRIX4, SUNOS4
		     * could be IRIX5, DECOSF, UCX, Ultrix, SUNOS5
		     * could be AIX, HP-UX
		     */
		    if ((fhp[2] == 0) && (fhp[3] == 0)) {
			/*
			 * bytes[2,3] == (0,0); rules out OSF, probably not UCX
			 * (unless the exported device name is just one letter!),
			 * could be Ultrix, IRIX5, AIX, or SUNOS5
			 * might be HP-UX (depends on their values for minor devs)
			 */
			if ((fhp[6] == 0) && (fhp[7] == 0)) {
			    fhtype = FHT_BSD44;
			}
			/*XXX we probably only need to test of these two bytes */
			else if ((len >= 24/4) && (fhp[21] == 0) && (fhp[23] == 0)) {
			    fhtype = FHT_ULTRIX;
			}
			else {
			    /* Could be SUNOS5/IRIX5, maybe AIX */
			    /* XXX no obvious difference between SUNOS5 and IRIX5 */
			    if (fhp[9] == 10)
				fhtype = FHT_SUNOS5;
			    /* XXX what about AIX? */
			}
		    }
		    else {
			/*
			 * bytes[2,3] != (0,0); rules out Ultrix, could be
			 * DECOSF, SUNOS5, IRIX5, AIX, HP-UX, or UCX
			 */
			if ((fhp[8] == 12) && (fhp[9] == 0)) {
			    fhtype = FHT_DECOSF;
			}
			else if ((fhp[8] == 0) && (fhp[9] == 10)) {
			    /* could be SUNOS5/IRIX5, AIX, HP-UX */
			    if ((fhp[7] == 0) && (fhp[6] == 0) &&
				(fhp[5] == 0) && (fhp[4] == 0)) {
				/* XXX is this always true of HP-UX? */
				fhtype = FHT_HPUX9;
			    }
			    else if (fhp[7] == 2) {
				/* This would be MNT_NFS on AIX, which is impossible */
				fhtype = FHT_SUNOS5;	/* or maybe IRIX5 */
			    }
			    else {
				/*
				 * XXX Could be SUNOS5/IRIX5 or AIX.  I don't
				 * XXX see any way to disambiguate these, so
				 * XXX I'm going with the more likely guess.
				 * XXX Sorry, Big Blue.
				 */
				fhtype = FHT_SUNOS5;	/* or maybe IRIX5 */
			    }
		        }
			else {
			    if (is_UCX(fhp, len)) {
				fhtype = FHT_VMSUCX;
			    }
			    else {
				fhtype = FHT_UNKNOWN;
			    }
			}
		    }
		}
	}

	/* XXX still needs to handle SUNOS3 */

	switch (fhtype) {
	case FHT_AUSPEX:
	    fsidp->Fsid_dev.Minor = fhp[7];
	    fsidp->Fsid_dev.Major = fhp[6];
	    fsidp->fsid_code = 0;

	    *inop = make_uint32(fhp[12], fhp[13], fhp[14], fhp[15]);

	    if (osnamep)
		*osnamep = "Auspex";
	    break;

	case FHT_BSD44:
	    fsidp->Fsid_dev.Minor = fhp[0];
	    fsidp->Fsid_dev.Major = fhp[1];
	    fsidp->fsid_code = 0;

	    *inop = make_uint32(fhp[15], fhp[14], fhp[13], fhp[12]);

	    if (osnamep)
		*osnamep = "BSD 4.4";
	    break;

	case FHT_DECOSF:
	    fsidp->fsid_code = make_uint32(fhp[7], fhp[6], fhp[5], fhp[4]);
			/* XXX could ignore 3 high-order bytes */

	    temp = make_uint32(fhp[3], fhp[2], fhp[1], fhp[0]);
	    fsidp->Fsid_dev.Minor = temp & 0xFFFFF;
	    fsidp->Fsid_dev.Major = (temp>>20) & 0xFFF;

	    *inop = make_uint32(fhp[15], fhp[14], fhp[13], fhp[12]);
	    if (osnamep)
		*osnamep = "OSF";
	    break;

	case FHT_IRIX4:
	    fsidp->Fsid_dev.Minor = fhp[3];
	    fsidp->Fsid_dev.Major = fhp[2];
	    fsidp->fsid_code = 0;

	    *inop = make_uint32(fhp[8], fhp[9], fhp[10], fhp[11]);

	    if (osnamep)
		*osnamep = "IRIX4";
	    break;

	case FHT_IRIX5:
	    fsidp->Fsid_dev.Minor = make_uint16(fhp[2], fhp[3]);
	    fsidp->Fsid_dev.Major = make_uint16(fhp[0], fhp[1]);
	    fsidp->fsid_code = make_uint32(fhp[4], fhp[5], fhp[6], fhp[7]);

	    *inop = make_uint32(fhp[12], fhp[13], fhp[14], fhp[15]);

	    if (osnamep)
		*osnamep = "IRIX5";
	    break;

#ifdef notdef
	case FHT_SUNOS3:
	    /*
	     * XXX - none of the heuristics above return this.
	     * Are there any SunOS 3.x systems around to care about?
	     */
	    if (osnamep)
		*osnamep = "SUNOS3";
	    break;
#endif

	case FHT_SUNOS4:
	    fsidp->Fsid_dev.Minor = fhp[3];
	    fsidp->Fsid_dev.Major = fhp[2];
	    fsidp->fsid_code = make_uint32(fhp[4], fhp[5], fhp[6], fhp[7]);

	    *inop = make_uint32(fhp[12], fhp[13], fhp[14], fhp[15]);

	    if (osnamep)
		*osnamep = "SUNOS4";
	    break;

	case FHT_SUNOS5:
	    temp = make_uint16(fhp[0], fhp[1]);
	    fsidp->Fsid_dev.Major = (temp>>2) &  0x3FFF;
	    temp = make_uint24(fhp[1], fhp[2], fhp[3]);
	    fsidp->Fsid_dev.Minor = temp & 0x3FFFF;
	    fsidp->fsid_code = make_uint32(fhp[4], fhp[5], fhp[6], fhp[7]);

	    *inop = make_uint32(fhp[12], fhp[13], fhp[14], fhp[15]);

	    if (osnamep)
		*osnamep = "SUNOS5";
	    break;

	case FHT_ULTRIX:
	    fsidp->fsid_code = 0;
	    fsidp->Fsid_dev.Minor = fhp[0];
	    fsidp->Fsid_dev.Major = fhp[1];

	    temp = make_uint32(fhp[7], fhp[6], fhp[5], fhp[4]);
	    *inop = temp;
	    if (osnamep)
		*osnamep = "Ultrix";
	    break;

	case FHT_VMSUCX:
	    /* No numeric file system ID, so hash on the device-name */
	    if (sizeof(*fsidp) >= 14) {
		if (sizeof(*fsidp) > 14)
		    memset((char *)fsidp, 0, sizeof(*fsidp));
		/* just use the whole thing */
		memcpy((char *)fsidp, (const char *)fh, 14);
	    }
	    else {
		uint32_t tempa[4];	/* at least 16 bytes, maybe more */

		memset((char *)tempa, 0, sizeof(tempa));
		memcpy((char *)tempa, (const char *)fh, 14); /* ensure alignment */
		fsidp->Fsid_dev.Minor = tempa[0] + (tempa[1]<<1);
		fsidp->Fsid_dev.Major = tempa[2] + (tempa[3]<<1);
		fsidp->fsid_code = 0;
	    }

	    /* VMS file ID is: (RVN, FidHi, FidLo) */
	    *inop = make_uint32(fhp[26], fhp[27], fhp[23], fhp[22]);

	    /* Caller must save (and null-terminate?) this value */
	    if (fsnamep)
		*fsnamep = (const char *)&(fhp[1]);

	    if (osnamep)
		*osnamep = "VMS";
	    break;

	case FHT_AIX32:
	    fsidp->Fsid_dev.Minor = make_uint16(fhp[2], fhp[3]);
	    fsidp->Fsid_dev.Major = make_uint16(fhp[0], fhp[1]);
	    fsidp->fsid_code = make_uint32(fhp[4], fhp[5], fhp[6], fhp[7]);

	    *inop = make_uint32(fhp[12], fhp[13], fhp[14], fhp[15]);

	    if (osnamep)
		*osnamep = "AIX32";
	    break;

	case FHT_HPUX9:
	    fsidp->Fsid_dev.Major = fhp[0];
	    temp = make_uint24(fhp[1], fhp[2], fhp[3]);
	    fsidp->Fsid_dev.Minor = temp;
	    fsidp->fsid_code = make_uint32(fhp[4], fhp[5], fhp[6], fhp[7]);

	    *inop = make_uint32(fhp[12], fhp[13], fhp[14], fhp[15]);

	    if (osnamep)
		*osnamep = "HPUX9";
	    break;

	case FHT_UNKNOWN:
#ifdef DEBUG
	    /* XXX debugging */
	    for (i = 0; i < len*4; i++)
		(void)fprintf(stderr, "%x.", fhp[i]);
	    (void)fprintf(stderr, "\n");
#endif
	    /* Save the actual handle, so it can be display with -u */
	    for (i = 0; i < len*4 && i*2 < sizeof(fsidp->Opaque_Handle) - 1; i++)
	    	(void)snprintf(&(fsidp->Opaque_Handle[i*2]), 3, "%.2X", fhp[i]);
	    fsidp->Opaque_Handle[i*2] = '\0';

	    /* XXX for now, give "bogus" values to aid debugging */
	    fsidp->fsid_code = 0;
	    fsidp->Fsid_dev.Minor = 257;
	    fsidp->Fsid_dev.Major = 257;
	    *inop = 1;

	    /* display will show this string instead of (257,257) */
	    if (fsnamep)
		*fsnamep = "Unknown";

	    if (osnamep)
		*osnamep = "Unknown";
	    break;

	}
}