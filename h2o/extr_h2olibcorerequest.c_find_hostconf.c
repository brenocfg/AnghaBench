#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_11__ {int len; int /*<<< orphan*/  base; } ;
typedef  TYPE_3__ h2o_iovec_t ;
struct TYPE_9__ {char* base; int len; } ;
struct TYPE_10__ {int port; TYPE_1__ host; } ;
struct TYPE_12__ {TYPE_2__ authority; } ;
typedef  TYPE_4__ h2o_hostconf_t ;

/* Variables and functions */
 char* alloca (int) ; 
 scalar_t__ h2o_memis (char*,int,char*,size_t) ; 
 int /*<<< orphan*/  h2o_strtolower (char*,int) ; 
 int /*<<< orphan*/ * h2o_url_parse_hostport (int /*<<< orphan*/ ,int,TYPE_3__*,int*) ; 
 scalar_t__ memcmp (char*,char*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static h2o_hostconf_t *find_hostconf(h2o_hostconf_t **hostconfs, h2o_iovec_t authority, uint16_t default_port)
{
    h2o_iovec_t hostname;
    uint16_t port;
    char *hostname_lc;

    /* safe-guard for alloca */
    if (authority.len >= 65536)
        return NULL;

    /* extract the specified hostname and port */
    if (h2o_url_parse_hostport(authority.base, authority.len, &hostname, &port) == NULL)
        return NULL;
    if (port == 65535)
        port = default_port;

    /* convert supplied hostname to lower-case */
    hostname_lc = alloca(hostname.len);
    memcpy(hostname_lc, hostname.base, hostname.len);
    h2o_strtolower(hostname_lc, hostname.len);

    do {
        h2o_hostconf_t *hostconf = *hostconfs;
        if (hostconf->authority.port == port || (hostconf->authority.port == 65535 && port == default_port)) {
            if (hostconf->authority.host.base[0] == '*') {
                /* matching against "*.foo.bar" */
                size_t cmplen = hostconf->authority.host.len - 1;
                if (cmplen < hostname.len &&
                    memcmp(hostconf->authority.host.base + 1, hostname_lc + hostname.len - cmplen, cmplen) == 0)
                    return hostconf;
            } else {
                /* exact match */
                if (h2o_memis(hostconf->authority.host.base, hostconf->authority.host.len, hostname_lc, hostname.len))
                    return hostconf;
            }
        }
    } while (*++hostconfs != NULL);

    return NULL;
}