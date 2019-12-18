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
#define  EACCES 150 
#define  EADDRINUSE 149 
#define  EADDRNOTAVAIL 148 
#define  EAGAIN 147 
#define  EAUTH 146 
#define  EBUSY 145 
#define  ECONNABORTED 144 
#define  ECONNREFUSED 143 
#define  ECONNRESET 142 
#define  EEXIST 141 
#define  EHOSTDOWN 140 
#define  EHOSTUNREACH 139 
#define  EISDIR 138 
#define  ENEEDAUTH 137 
#define  ENETDOWN 136 
#define  ENETRESET 135 
#define  ENETUNREACH 134 
#define  ENOENT 133 
#define  ENOMEM 132 
#define  ENOSPC 131 
#define  EPERM 130 
#define  EROFS 129 
#define  ETIMEDOUT 128 
 int /*<<< orphan*/  FETCH_ABORT ; 
 int /*<<< orphan*/  FETCH_AUTH ; 
 int /*<<< orphan*/  FETCH_DOWN ; 
 int /*<<< orphan*/  FETCH_EXISTS ; 
 int /*<<< orphan*/  FETCH_FULL ; 
 int /*<<< orphan*/  FETCH_MEMORY ; 
 int /*<<< orphan*/  FETCH_NETWORK ; 
 int /*<<< orphan*/  FETCH_OK ; 
 int /*<<< orphan*/  FETCH_TEMP ; 
 int /*<<< orphan*/  FETCH_TIMEOUT ; 
 int /*<<< orphan*/  FETCH_UNAVAIL ; 
 int /*<<< orphan*/  FETCH_UNKNOWN ; 
 int /*<<< orphan*/  MAXERRSTRING ; 
 int errno ; 
 int /*<<< orphan*/  fetchLastErrCode ; 
 int /*<<< orphan*/  fetchLastErrString ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 char* strerror (int) ; 

void
fetch_syserr(void)
{
	switch (errno) {
	case 0:
		fetchLastErrCode = FETCH_OK;
		break;
	case EPERM:
	case EACCES:
	case EROFS:
	case EAUTH:
	case ENEEDAUTH:
		fetchLastErrCode = FETCH_AUTH;
		break;
	case ENOENT:
	case EISDIR: /* XXX */
		fetchLastErrCode = FETCH_UNAVAIL;
		break;
	case ENOMEM:
		fetchLastErrCode = FETCH_MEMORY;
		break;
	case EBUSY:
	case EAGAIN:
		fetchLastErrCode = FETCH_TEMP;
		break;
	case EEXIST:
		fetchLastErrCode = FETCH_EXISTS;
		break;
	case ENOSPC:
		fetchLastErrCode = FETCH_FULL;
		break;
	case EADDRINUSE:
	case EADDRNOTAVAIL:
	case ENETDOWN:
	case ENETUNREACH:
	case ENETRESET:
	case EHOSTUNREACH:
		fetchLastErrCode = FETCH_NETWORK;
		break;
	case ECONNABORTED:
	case ECONNRESET:
		fetchLastErrCode = FETCH_ABORT;
		break;
	case ETIMEDOUT:
		fetchLastErrCode = FETCH_TIMEOUT;
		break;
	case ECONNREFUSED:
	case EHOSTDOWN:
		fetchLastErrCode = FETCH_DOWN;
		break;
	default:
		fetchLastErrCode = FETCH_UNKNOWN;
	}
	snprintf(fetchLastErrString, MAXERRSTRING, "%s", strerror(errno));
}