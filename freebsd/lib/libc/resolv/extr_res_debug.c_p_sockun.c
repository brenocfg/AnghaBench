#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sin_family; int /*<<< orphan*/  sin_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  sin6_addr; } ;
union res_sockaddr_union {TYPE_1__ sin; TYPE_2__ sin6; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  inet_ntop (int const,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 

const char *
p_sockun(union res_sockaddr_union u, char *buf, size_t size) {
	char ret[sizeof "ffff:ffff:ffff:ffff:ffff:ffff:123.123.123.123"];

	switch (u.sin.sin_family) {
	case AF_INET:
		inet_ntop(AF_INET, &u.sin.sin_addr, ret, sizeof ret);
		break;
#ifdef HAS_INET6_STRUCTS
	case AF_INET6:
		inet_ntop(AF_INET6, &u.sin6.sin6_addr, ret, sizeof ret);
		break;
#endif
	default:
		sprintf(ret, "[af%d]", u.sin.sin_family);
		break;
	}
	if (size > 0U) {
		strncpy(buf, ret, size - 1);
		buf[size - 1] = '0';
	}
	return (buf);
}