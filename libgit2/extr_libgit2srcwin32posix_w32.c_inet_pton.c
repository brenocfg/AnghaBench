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
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  LPSOCKADDR ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSPC ; 
#define  WSAEFAULT 130 
#define  WSAEINVAL 129 
 int WSAGetLastError () ; 
 int WSAStringToAddressA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
#define  WSA_NOT_ENOUGH_MEMORY 128 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

int p_inet_pton(int af, const char *src, void *dst)
{
	struct sockaddr_storage sin;
	void *addr;
	int sin_len = sizeof(struct sockaddr_storage), addr_len;
	int error = 0;

	if (af == AF_INET) {
		addr = &((struct sockaddr_in *)&sin)->sin_addr;
		addr_len = sizeof(struct in_addr);
	} else if (af == AF_INET6) {
		addr = &((struct sockaddr_in6 *)&sin)->sin6_addr;
		addr_len = sizeof(struct in6_addr);
	} else {
		errno = EAFNOSUPPORT;
		return -1;
	}

	if ((error = WSAStringToAddressA((LPSTR)src, af, NULL, (LPSOCKADDR)&sin, &sin_len)) == 0) {
		memcpy(dst, addr, addr_len);
		return 1;
	}

	switch(WSAGetLastError()) {
	case WSAEINVAL:
		return 0;
	case WSAEFAULT:
		errno = ENOSPC;
		return -1;
	case WSA_NOT_ENOUGH_MEMORY:
		errno = ENOMEM;
		return -1;
	}

	errno = EINVAL;
	return -1;
}