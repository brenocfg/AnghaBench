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
typedef  int u_long ;

/* Variables and functions */
#define  RES_AAONLY 147 
#define  RES_DEBUG 146 
#define  RES_DEFNAMES 145 
#define  RES_DNSRCH 144 
#define  RES_IGNTC 143 
#define  RES_INIT 142 
#define  RES_INSECURE1 141 
#define  RES_INSECURE2 140 
#define  RES_NOALIASES 139 
#define  RES_NOTLDQUERY 138 
#define  RES_NO_NIBBLE2 137 
#define  RES_NSID 136 
#define  RES_PRIMARY 135 
#define  RES_RECURSE 134 
#define  RES_STAYOPEN 133 
#define  RES_USEVC 132 
#define  RES_USE_DNAME 131 
#define  RES_USE_DNSSEC 130 
#define  RES_USE_EDNS0 129 
#define  RES_USE_INET6 128 
 char* p_option_nbuf ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char *
p_option(u_long option) {
	char *nbuf = p_option_nbuf;

	switch (option) {
	case RES_INIT:		return "init";
	case RES_DEBUG:		return "debug";
	case RES_AAONLY:	return "aaonly(unimpl)";
	case RES_USEVC:		return "usevc";
	case RES_PRIMARY:	return "primry(unimpl)";
	case RES_IGNTC:		return "igntc";
	case RES_RECURSE:	return "recurs";
	case RES_DEFNAMES:	return "defnam";
	case RES_STAYOPEN:	return "styopn";
	case RES_DNSRCH:	return "dnsrch";
	case RES_INSECURE1:	return "insecure1";
	case RES_INSECURE2:	return "insecure2";
	case RES_NOALIASES:	return "noaliases";
	case RES_USE_INET6:	return "inet6";
#ifdef RES_USE_EDNS0	/*%< KAME extension */
	case RES_USE_EDNS0:	return "edns0";
	case RES_NSID:		return "nsid";
#endif
#ifdef RES_USE_DNAME
	case RES_USE_DNAME:	return "dname";
#endif
#ifdef RES_USE_DNSSEC
	case RES_USE_DNSSEC:	return "dnssec";
#endif
#ifdef RES_NOTLDQUERY
	case RES_NOTLDQUERY:	return "no-tld-query";
#endif
#ifdef RES_NO_NIBBLE2
	case RES_NO_NIBBLE2:	return "no-nibble2";
#endif
				/* XXX nonreentrant */
	default:		sprintf(nbuf, "?0x%lx?", (u_long)option);
				return (nbuf);
	}
}