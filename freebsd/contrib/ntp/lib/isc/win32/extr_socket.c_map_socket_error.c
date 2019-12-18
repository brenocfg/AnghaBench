#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  connected; } ;
typedef  TYPE_1__ isc_socket_t ;

/* Variables and functions */
 int DOIO_HARD ; 
 int DOIO_SOFT ; 
#define  ERROR_CONNECTION_ABORTED 149 
#define  ERROR_HOST_UNREACHABLE 148 
#define  ERROR_NETNAME_DELETED 147 
#define  ERROR_NETWORK_UNREACHABLE 146 
#define  ERROR_OPERATION_ABORTED 145 
#define  ERROR_PORT_UNREACHABLE 144 
#define  ERROR_REQUEST_ABORTED 143 
 int ISC_R_ADDRNOTAVAIL ; 
 int ISC_R_BADADDRESSFORM ; 
 int ISC_R_CONNECTIONRESET ; 
 int ISC_R_CONNREFUSED ; 
 int ISC_R_FAMILYNOSUPPORT ; 
 int ISC_R_HOSTDOWN ; 
 int ISC_R_HOSTUNREACH ; 
 int ISC_R_IOERROR ; 
 int ISC_R_NETDOWN ; 
 int ISC_R_NETUNREACH ; 
 int ISC_R_NOPERM ; 
 int ISC_R_NORESOURCES ; 
 int ISC_R_NOTCONNECTED ; 
#define  WSAEACCES 142 
#define  WSAEADDRNOTAVAIL 141 
#define  WSAEAFNOSUPPORT 140 
#define  WSAECONNABORTED 139 
#define  WSAECONNREFUSED 138 
#define  WSAECONNRESET 137 
#define  WSAEDESTADDRREQ 136 
#define  WSAEDISCON 135 
#define  WSAEHOSTDOWN 134 
#define  WSAEHOSTUNREACH 133 
#define  WSAENETDOWN 132 
#define  WSAENETRESET 131 
#define  WSAENETUNREACH 130 
#define  WSAENOBUFS 129 
#define  WSAENOTCONN 128 
 int /*<<< orphan*/  isc__strerror (int,char*,size_t) ; 

int
map_socket_error(isc_socket_t *sock, int windows_errno, int *isc_errno,
		 char *errorstring, size_t bufsize) {

	int doreturn;
	switch (windows_errno) {
	case WSAECONNREFUSED:
		*isc_errno = ISC_R_CONNREFUSED;
		if (sock->connected)
			doreturn = DOIO_HARD;
		else
			doreturn = DOIO_SOFT;
		break;
	case WSAENETUNREACH:
	case ERROR_NETWORK_UNREACHABLE:
		*isc_errno = ISC_R_NETUNREACH;
		if (sock->connected)
			doreturn = DOIO_HARD;
		else
			doreturn = DOIO_SOFT;
		break;
	case ERROR_PORT_UNREACHABLE:
	case ERROR_HOST_UNREACHABLE:
	case WSAEHOSTUNREACH:
		*isc_errno = ISC_R_HOSTUNREACH;
		if (sock->connected)
			doreturn = DOIO_HARD;
		else
			doreturn = DOIO_SOFT;
		break;
	case WSAENETDOWN:
		*isc_errno = ISC_R_NETDOWN;
		if (sock->connected)
			doreturn = DOIO_HARD;
		else
			doreturn = DOIO_SOFT;
		break;
	case WSAEHOSTDOWN:
		*isc_errno = ISC_R_HOSTDOWN;
		if (sock->connected)
			doreturn = DOIO_HARD;
		else
			doreturn = DOIO_SOFT;
		break;
	case WSAEACCES:
		*isc_errno = ISC_R_NOPERM;
		if (sock->connected)
			doreturn = DOIO_HARD;
		else
			doreturn = DOIO_SOFT;
		break;
	case WSAECONNRESET:
	case WSAENETRESET:
	case WSAECONNABORTED:
	case WSAEDISCON:
		*isc_errno = ISC_R_CONNECTIONRESET;
		if (sock->connected)
			doreturn = DOIO_HARD;
		else
			doreturn = DOIO_SOFT;
		break;
	case WSAENOTCONN:
		*isc_errno = ISC_R_NOTCONNECTED;
		if (sock->connected)
			doreturn = DOIO_HARD;
		else
			doreturn = DOIO_SOFT;
		break;
	case ERROR_OPERATION_ABORTED:
	case ERROR_CONNECTION_ABORTED:
	case ERROR_REQUEST_ABORTED:
		*isc_errno = ISC_R_CONNECTIONRESET;
		doreturn = DOIO_HARD;
		break;
	case WSAENOBUFS:
		*isc_errno = ISC_R_NORESOURCES;
		doreturn = DOIO_HARD;
		break;
	case WSAEAFNOSUPPORT:
		*isc_errno = ISC_R_FAMILYNOSUPPORT;
		doreturn = DOIO_HARD;
		break;
	case WSAEADDRNOTAVAIL:
		*isc_errno = ISC_R_ADDRNOTAVAIL;
		doreturn = DOIO_HARD;
		break;
	case WSAEDESTADDRREQ:
		*isc_errno = ISC_R_BADADDRESSFORM;
		doreturn = DOIO_HARD;
		break;
	case ERROR_NETNAME_DELETED:
		*isc_errno = ISC_R_NETDOWN;
		doreturn = DOIO_HARD;
		break;
	default:
		*isc_errno = ISC_R_IOERROR;
		doreturn = DOIO_HARD;
		break;
	}
	if (doreturn == DOIO_HARD) {
		isc__strerror(windows_errno, errorstring, bufsize);
	}
	return (doreturn);
}