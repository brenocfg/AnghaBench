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
#define  WSAEACCES 171 
#define  WSAEADDRINUSE 170 
#define  WSAEADDRNOTAVAIL 169 
#define  WSAEAFNOSUPPORT 168 
#define  WSAEALREADY 167 
#define  WSAEBADF 166 
#define  WSAECONNABORTED 165 
#define  WSAECONNREFUSED 164 
#define  WSAECONNRESET 163 
#define  WSAEDESTADDRREQ 162 
#define  WSAEDISCON 161 
#define  WSAEFAULT 160 
#define  WSAEHOSTDOWN 159 
#define  WSAEINPROGRESS 158 
#define  WSAEINTR 157 
#define  WSAEINVAL 156 
#define  WSAEISCONN 155 
#define  WSAELOOP 154 
#define  WSAEMFILE 153 
#define  WSAEMSGSIZE 152 
#define  WSAENAMETOOLONG 151 
#define  WSAENETDOWN 150 
#define  WSAENETRESET 149 
#define  WSAENETUNREACH 148 
#define  WSAENOBUFS 147 
#define  WSAENOPROTOOPT 146 
#define  WSAENOTCONN 145 
#define  WSAENOTSOCK 144 
#define  WSAEOPNOTSUPP 143 
#define  WSAEPFNOSUPPORT 142 
#define  WSAEPROTONOSUPPORT 141 
#define  WSAEPROTOTYPE 140 
#define  WSAESHUTDOWN 139 
#define  WSAESOCKTNOSUPPORT 138 
#define  WSAETIMEDOUT 137 
#define  WSAETOOMANYREFS 136 
#define  WSAEWOULDBLOCK 135 
#define  WSAHOST_NOT_FOUND 134 
#define  WSANOTINITIALISED 133 
#define  WSANO_DATA 132 
#define  WSANO_RECOVERY 131 
#define  WSASYSNOTREADY 130 
#define  WSATRY_AGAIN 129 
#define  WSAVERNOTSUPPORTED 128 
 int socketError ; 
 char* strerror (int) ; 

char *NET_ErrorString( void ) {
#ifdef _WIN32
	//FIXME: replace with FormatMessage?
	switch( socketError ) {
		case WSAEINTR: return "WSAEINTR";
		case WSAEBADF: return "WSAEBADF";
		case WSAEACCES: return "WSAEACCES";
		case WSAEDISCON: return "WSAEDISCON";
		case WSAEFAULT: return "WSAEFAULT";
		case WSAEINVAL: return "WSAEINVAL";
		case WSAEMFILE: return "WSAEMFILE";
		case WSAEWOULDBLOCK: return "WSAEWOULDBLOCK";
		case WSAEINPROGRESS: return "WSAEINPROGRESS";
		case WSAEALREADY: return "WSAEALREADY";
		case WSAENOTSOCK: return "WSAENOTSOCK";
		case WSAEDESTADDRREQ: return "WSAEDESTADDRREQ";
		case WSAEMSGSIZE: return "WSAEMSGSIZE";
		case WSAEPROTOTYPE: return "WSAEPROTOTYPE";
		case WSAENOPROTOOPT: return "WSAENOPROTOOPT";
		case WSAEPROTONOSUPPORT: return "WSAEPROTONOSUPPORT";
		case WSAESOCKTNOSUPPORT: return "WSAESOCKTNOSUPPORT";
		case WSAEOPNOTSUPP: return "WSAEOPNOTSUPP";
		case WSAEPFNOSUPPORT: return "WSAEPFNOSUPPORT";
		case WSAEAFNOSUPPORT: return "WSAEAFNOSUPPORT";
		case WSAEADDRINUSE: return "WSAEADDRINUSE";
		case WSAEADDRNOTAVAIL: return "WSAEADDRNOTAVAIL";
		case WSAENETDOWN: return "WSAENETDOWN";
		case WSAENETUNREACH: return "WSAENETUNREACH";
		case WSAENETRESET: return "WSAENETRESET";
		case WSAECONNABORTED: return "WSWSAECONNABORTEDAEINTR";
		case WSAECONNRESET: return "WSAECONNRESET";
		case WSAENOBUFS: return "WSAENOBUFS";
		case WSAEISCONN: return "WSAEISCONN";
		case WSAENOTCONN: return "WSAENOTCONN";
		case WSAESHUTDOWN: return "WSAESHUTDOWN";
		case WSAETOOMANYREFS: return "WSAETOOMANYREFS";
		case WSAETIMEDOUT: return "WSAETIMEDOUT";
		case WSAECONNREFUSED: return "WSAECONNREFUSED";
		case WSAELOOP: return "WSAELOOP";
		case WSAENAMETOOLONG: return "WSAENAMETOOLONG";
		case WSAEHOSTDOWN: return "WSAEHOSTDOWN";
		case WSASYSNOTREADY: return "WSASYSNOTREADY";
		case WSAVERNOTSUPPORTED: return "WSAVERNOTSUPPORTED";
		case WSANOTINITIALISED: return "WSANOTINITIALISED";
		case WSAHOST_NOT_FOUND: return "WSAHOST_NOT_FOUND";
		case WSATRY_AGAIN: return "WSATRY_AGAIN";
		case WSANO_RECOVERY: return "WSANO_RECOVERY";
		case WSANO_DATA: return "WSANO_DATA";
		default: return "NO ERROR";
	}
#else
	return strerror(socketError);
#endif
}