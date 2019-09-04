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

int ptls_server_name_is_ipaddr(const char *name)
{
#ifdef AF_INET
    struct sockaddr_in sin;
    if (inet_pton(AF_INET, name, &sin) == 1)
        return 1;
#endif
#ifdef AF_INET6
    struct sockaddr_in6 sin6;
    if (inet_pton(AF_INET6, name, &sin6) == 1)
        return 1;
#endif
    return 0;
}