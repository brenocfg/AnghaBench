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
typedef  int ypxfrstat ;

/* Variables and functions */
#define  YPXFR_AGE 143 
#define  YPXFR_BADARGS 142 
#define  YPXFR_CLEAR 141 
#define  YPXFR_DBM 140 
#define  YPXFR_FILE 139 
#define  YPXFR_FORCE 138 
#define  YPXFR_MADDR 137 
#define  YPXFR_NODOM 136 
#define  YPXFR_NOMAP 135 
#define  YPXFR_REFUSED 134 
#define  YPXFR_RPC 133 
#define  YPXFR_RSRC 132 
#define  YPXFR_SKEW 131 
#define  YPXFR_SUCC 130 
#define  YPXFR_XFRERR 129 
#define  YPXFR_YPERR 128 

const char *
ypxfrerr_string(ypxfrstat code)
{
	switch (code) {
	case YPXFR_SUCC:
		return ("Map successfully transferred");
		break;
	case YPXFR_AGE:
		return ("Master's version not newer");
		break;
	case YPXFR_NOMAP:
		return ("No such map in server's domain");
		break;
	case YPXFR_NODOM:
		return ("Domain not supported by server");
		break;
	case YPXFR_RSRC:
		return ("Local resource allocation failure");
		break;
	case YPXFR_RPC:
		return ("RPC failure talking to server");
		break;
	case YPXFR_MADDR:
		return ("Could not get master server address");
		break;
	case YPXFR_YPERR:
		return ("NIS server/map database error");
		break;
	case YPXFR_BADARGS:
		return ("Request arguments bad");
		break;
	case YPXFR_DBM:
		return ("Local database operation failed");
		break;
	case YPXFR_FILE:
		return ("Local file I/O operation failed");
		break;
	case YPXFR_SKEW:
		return ("Map version skew during transfer");
		break;
	case YPXFR_CLEAR:
		return ("Couldn't send \"clear\" request to local ypserv");
		break;
	case YPXFR_FORCE:
		return ("No local order number in map -- use -f flag");
		break;
	case YPXFR_XFRERR:
		return ("General ypxfr error");
		break;
	case YPXFR_REFUSED:
		return ("Transfer request refused by ypserv");
		break;
	default:
		return ("Unknown error code");
		break;
	}
}