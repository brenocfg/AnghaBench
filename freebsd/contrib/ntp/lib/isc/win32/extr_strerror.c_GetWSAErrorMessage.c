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
#define  WSAEACCES 174 
#define  WSAEADDRINUSE 173 
#define  WSAEADDRNOTAVAIL 172 
#define  WSAEAFNOSUPPORT 171 
#define  WSAEALREADY 170 
#define  WSAEBADF 169 
#define  WSAECONNABORTED 168 
#define  WSAECONNREFUSED 167 
#define  WSAECONNRESET 166 
#define  WSAEDESTADDRREQ 165 
#define  WSAEDISCON 164 
#define  WSAEDQUOT 163 
#define  WSAEFAULT 162 
#define  WSAEHOSTDOWN 161 
#define  WSAEHOSTUNREACH 160 
#define  WSAEINPROGRESS 159 
#define  WSAEINTR 158 
#define  WSAEINVAL 157 
#define  WSAEISCONN 156 
#define  WSAELOOP 155 
#define  WSAEMFILE 154 
#define  WSAEMSGSIZE 153 
#define  WSAENAMETOOLONG 152 
#define  WSAENETDOWN 151 
#define  WSAENETRESET 150 
#define  WSAENETUNREACH 149 
#define  WSAENOBUFS 148 
#define  WSAENOPROTOOPT 147 
#define  WSAENOTCONN 146 
#define  WSAENOTEMPTY 145 
#define  WSAENOTSOCK 144 
#define  WSAEOPNOTSUPP 143 
#define  WSAEPFNOSUPPORT 142 
#define  WSAEPROCLIM 141 
#define  WSAEPROTONOSUPPORT 140 
#define  WSAEPROTOTYPE 139 
#define  WSAEREMOTE 138 
#define  WSAESHUTDOWN 137 
#define  WSAESOCKTNOSUPPORT 136 
#define  WSAESTALE 135 
#define  WSAETIMEDOUT 134 
#define  WSAETOOMANYREFS 133 
#define  WSAEUSERS 132 
#define  WSAEWOULDBLOCK 131 
#define  WSANOTINITIALISED 130 
#define  WSASYSNOTREADY 129 
#define  WSAVERNOTSUPPORTED 128 

char *
GetWSAErrorMessage(int errval) {
	char *msg;

	switch (errval) {

	case WSAEINTR:
		msg = "Interrupted system call";
		break;

	case WSAEBADF:
		msg = "Bad file number";
		break;

	case WSAEACCES:
		msg = "Permission denied";
		break;

	case WSAEFAULT:
		msg = "Bad address";
		break;

	case WSAEINVAL:
		msg = "Invalid argument";
		break;

	case WSAEMFILE:
		msg = "Too many open sockets";
		break;

	case WSAEWOULDBLOCK:
		msg = "Operation would block";
		break;

	case WSAEINPROGRESS:
		msg = "Operation now in progress";
		break;

	case WSAEALREADY:
		msg = "Operation already in progress";
		break;

	case WSAENOTSOCK:
		msg = "Socket operation on non-socket";
		break;

	case WSAEDESTADDRREQ:
		msg = "Destination address required";
		break;

	case WSAEMSGSIZE:
		msg = "Message too long";
		break;

	case WSAEPROTOTYPE:
		msg = "Protocol wrong type for socket";
		break;

	case WSAENOPROTOOPT:
		msg = "Bad protocol option";
		break;

	case WSAEPROTONOSUPPORT:
		msg = "Protocol not supported";
		break;

	case WSAESOCKTNOSUPPORT:
		msg = "Socket type not supported";
		break;

	case WSAEOPNOTSUPP:
		msg = "Operation not supported on socket";
		break;

	case WSAEPFNOSUPPORT:
		msg = "Protocol family not supported";
		break;

	case WSAEAFNOSUPPORT:
		msg = "Address family not supported";
		break;

	case WSAEADDRINUSE:
		msg = "Address already in use";
		break;

	case WSAEADDRNOTAVAIL:
		msg = "Can't assign requested address";
		break;

	case WSAENETDOWN:
		msg = "Network is down";
		break;

	case WSAENETUNREACH:
		msg = "Network is unreachable";
		break;

	case WSAENETRESET:
		msg = "Net connection reset";
		break;

	case WSAECONNABORTED:
		msg = "Software caused connection abort";
		break;

	case WSAECONNRESET:
		msg = "Connection reset by peer";
		break;

	case WSAENOBUFS:
		msg = "No buffer space available";
		break;

	case WSAEISCONN:
		msg = "Socket is already connected";
		break;

	case WSAENOTCONN:
		msg = "Socket is not connected";
		break;

	case WSAESHUTDOWN:
		msg = "Can't send after socket shutdown";
		break;

	case WSAETOOMANYREFS:
		msg = "Too many references: can't splice";
		break;

	case WSAETIMEDOUT:
		msg = "Connection timed out";
		break;

	case WSAECONNREFUSED:
		msg = "Connection refused";
		break;

	case WSAELOOP:
		msg = "Too many levels of symbolic links";
		break;

	case WSAENAMETOOLONG:
		msg = "File name too long";
		break;

	case WSAEHOSTDOWN:
		msg = "Host is down";
		break;

	case WSAEHOSTUNREACH:
		msg = "No route to host";
		break;

	case WSAENOTEMPTY:
		msg = "Directory not empty";
		break;

	case WSAEPROCLIM:
		msg = "Too many processes";
		break;

	case WSAEUSERS:
		msg = "Too many users";
		break;

	case WSAEDQUOT:
		msg = "Disc quota exceeded";
		break;

	case WSAESTALE:
		msg = "Stale NFS file handle";
		break;

	case WSAEREMOTE:
		msg = "Too many levels of remote in path";
		break;

	case WSASYSNOTREADY:
		msg = "Network system is unavailable";
		break;

	case WSAVERNOTSUPPORTED:
		msg = "Winsock version out of range";
		break;

	case WSANOTINITIALISED:
		msg = "WSAStartup not yet called";
		break;

	case WSAEDISCON:
		msg = "Graceful shutdown in progress";
		break;
/*
	case WSAHOST_NOT_FOUND:
		msg = "Host not found";
		break;

	case WSANO_DATA:
		msg = "No host data of that type was found";
		break;
*/
	default:
		msg = NULL;
		break;
	}
	return (msg);
}