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
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct TYPE_3__ {int len; int base; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 char const* h2o_url_host_to_sun_err_is_not_unix_socket ; 
 scalar_t__ memcmp (int,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 

const char *h2o_url_host_to_sun(h2o_iovec_t host, struct sockaddr_un *sa)
{
#define PREFIX "unix:"

    if (host.len < sizeof(PREFIX) - 1 || memcmp(host.base, PREFIX, sizeof(PREFIX) - 1) != 0)
        return h2o_url_host_to_sun_err_is_not_unix_socket;

    if (host.len - sizeof(PREFIX) - 1 >= sizeof(sa->sun_path))
        return "unix-domain socket path is too long";

    memset(sa, 0, sizeof(*sa));
    sa->sun_family = AF_UNIX;
    memcpy(sa->sun_path, host.base + sizeof(PREFIX) - 1, host.len - (sizeof(PREFIX) - 1));
    return NULL;

#undef PREFIX
}