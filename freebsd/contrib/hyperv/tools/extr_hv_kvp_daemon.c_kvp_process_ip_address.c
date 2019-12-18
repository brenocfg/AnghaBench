#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  s6_addr; } ;
struct sockaddr_in6 {TYPE_1__ sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;

/* Variables and functions */
 int AF_INET ; 
 int EINVAL ; 
 int INET6_ADDRSTRLEN ; 
 int INET_ADDRSTRLEN ; 
 int errno ; 
 char* inet_ntop (int,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int
kvp_process_ip_address(void *addrp,
    int family, char *buffer,
    int length, int *offset)
{
	struct sockaddr_in *addr;
	struct sockaddr_in6 *addr6;
	int addr_length;
	char tmp[50];
	const char *str;

	if (family == AF_INET) {
		addr = (struct sockaddr_in *)addrp;
		str = inet_ntop(family, &addr->sin_addr, tmp, 50);
		addr_length = INET_ADDRSTRLEN;
	} else {
		addr6 = (struct sockaddr_in6 *)addrp;
		str = inet_ntop(family, &addr6->sin6_addr.s6_addr, tmp, 50);
		addr_length = INET6_ADDRSTRLEN;
	}

	if ((length - *offset) < addr_length + 1) {
		return (EINVAL);
	}
	if (str == NULL) {
		strlcpy(buffer, "inet_ntop failed\n", length);
		return (errno);
	}
	if (*offset == 0) {
		strlcpy(buffer, tmp, length);
	} else{
		strlcat(buffer, tmp, length);
	}
	strlcat(buffer, ";", length);

	*offset += strlen(str) + 1;
	return (0);
}