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

/* Variables and functions */
#define  YPERR_ACCESS 143 
#define  YPERR_BADARGS 142 
#define  YPERR_BADDB 141 
#define  YPERR_BUSY 140 
#define  YPERR_DOMAIN 139 
#define  YPERR_KEY 138 
#define  YPERR_MAP 137 
#define  YPERR_NODOM 136 
#define  YPERR_NOMORE 135 
#define  YPERR_PMAP 134 
#define  YPERR_RESRC 133 
#define  YPERR_RPC 132 
#define  YPERR_VERS 131 
#define  YPERR_YPBIND 130 
#define  YPERR_YPERR 129 
#define  YPERR_YPSERV 128 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char *
yperr_string(int incode)
{
	static char err[80];

	switch (incode) {
	case 0:
		return ("Success");
	case YPERR_BADARGS:
		return ("Request arguments bad");
	case YPERR_RPC:
		return ("RPC failure");
	case YPERR_DOMAIN:
		return ("Can't bind to server which serves this domain");
	case YPERR_MAP:
		return ("No such map in server's domain");
	case YPERR_KEY:
		return ("No such key in map");
	case YPERR_YPERR:
		return ("YP server error");
	case YPERR_RESRC:
		return ("Local resource allocation failure");
	case YPERR_NOMORE:
		return ("No more records in map database");
	case YPERR_PMAP:
		return ("Can't communicate with portmapper");
	case YPERR_YPBIND:
		return ("Can't communicate with ypbind");
	case YPERR_YPSERV:
		return ("Can't communicate with ypserv");
	case YPERR_NODOM:
		return ("Local domain name not set");
	case YPERR_BADDB:
		return ("Server data base is bad");
	case YPERR_VERS:
		return ("YP server version mismatch - server can't supply service.");
	case YPERR_ACCESS:
		return ("Access violation");
	case YPERR_BUSY:
		return ("Database is busy");
	}
	sprintf(err, "YP unknown error %d\n", incode);
	return (err);
}