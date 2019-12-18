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
typedef  int bpf_u_int32 ;

/* Variables and functions */
#define  DL_ACCESS 155 
#define  DL_BADADDR 154 
#define  DL_BADCORR 153 
#define  DL_BADDATA 152 
#define  DL_BADPPA 151 
#define  DL_BADPRIM 150 
#define  DL_BADQOSPARAM 149 
#define  DL_BADQOSTYPE 148 
#define  DL_BADSAP 147 
#define  DL_BADTOKEN 146 
#define  DL_BOUND 145 
#define  DL_BUSY 144 
#define  DL_INITFAILED 143 
#define  DL_NOADDR 142 
#define  DL_NOAUTO 141 
#define  DL_NOTENAB 140 
#define  DL_NOTESTAUTO 139 
#define  DL_NOTINIT 138 
#define  DL_NOTSUPPORTED 137 
#define  DL_NOXIDAUTO 136 
#define  DL_OUTSTATE 135 
#define  DL_PENDING 134 
#define  DL_SYSERR 133 
#define  DL_TESTAUTO 132 
#define  DL_TOOMANY 131 
#define  DL_UNDELIVERABLE 130 
#define  DL_UNSUPPORTED 129 
#define  DL_XIDAUTO 128 
 int /*<<< orphan*/  pcap_snprintf (char*,size_t,char*,int) ; 

__attribute__((used)) static char *
dlstrerror(char *errbuf, size_t errbufsize, bpf_u_int32 dl_errno)
{
	switch (dl_errno) {

	case DL_ACCESS:
		return ("Improper permissions for request");

	case DL_BADADDR:
		return ("DLSAP addr in improper format or invalid");

	case DL_BADCORR:
		return ("Seq number not from outstand DL_CONN_IND");

	case DL_BADDATA:
		return ("User data exceeded provider limit");

	case DL_BADPPA:
#ifdef HAVE_DEV_DLPI
		/*
		 * With a single "/dev/dlpi" device used for all
		 * DLPI providers, PPAs have nothing to do with
		 * unit numbers.
		 */
		return ("Specified PPA was invalid");
#else
		/*
		 * We have separate devices for separate devices;
		 * the PPA is just the unit number.
		 */
		return ("Specified PPA (device unit) was invalid");
#endif

	case DL_BADPRIM:
		return ("Primitive received not known by provider");

	case DL_BADQOSPARAM:
		return ("QOS parameters contained invalid values");

	case DL_BADQOSTYPE:
		return ("QOS structure type is unknown/unsupported");

	case DL_BADSAP:
		return ("Bad LSAP selector");

	case DL_BADTOKEN:
		return ("Token used not an active stream");

	case DL_BOUND:
		return ("Attempted second bind with dl_max_conind");

	case DL_INITFAILED:
		return ("Physical link initialization failed");

	case DL_NOADDR:
		return ("Provider couldn't allocate alternate address");

	case DL_NOTINIT:
		return ("Physical link not initialized");

	case DL_OUTSTATE:
		return ("Primitive issued in improper state");

	case DL_SYSERR:
		return ("UNIX system error occurred");

	case DL_UNSUPPORTED:
		return ("Requested service not supplied by provider");

	case DL_UNDELIVERABLE:
		return ("Previous data unit could not be delivered");

	case DL_NOTSUPPORTED:
		return ("Primitive is known but not supported");

	case DL_TOOMANY:
		return ("Limit exceeded");

	case DL_NOTENAB:
		return ("Promiscuous mode not enabled");

	case DL_BUSY:
		return ("Other streams for PPA in post-attached");

	case DL_NOAUTO:
		return ("Automatic handling XID&TEST not supported");

	case DL_NOXIDAUTO:
		return ("Automatic handling of XID not supported");

	case DL_NOTESTAUTO:
		return ("Automatic handling of TEST not supported");

	case DL_XIDAUTO:
		return ("Automatic handling of XID response");

	case DL_TESTAUTO:
		return ("Automatic handling of TEST response");

	case DL_PENDING:
		return ("Pending outstanding connect indications");

	default:
		pcap_snprintf(errbuf, errbufsize, "Error %02x", dl_errno);
		return (errbuf);
	}
}