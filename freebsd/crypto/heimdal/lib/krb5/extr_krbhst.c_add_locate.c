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
struct sockaddr {int dummy; } ;
struct krb5_krbhst_info {char* hostname; struct addrinfo* ai; int /*<<< orphan*/  def_port; int /*<<< orphan*/  port; int /*<<< orphan*/  proto; } ;
struct krb5_krbhst_data {int dummy; } ;
struct addrinfo {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  port ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  host ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int NI_MAXHOST ; 
 int NI_MAXSERV ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 int /*<<< orphan*/  append_host_hostinfo (struct krb5_krbhst_data*,struct krb5_krbhst_info*) ; 
 struct krb5_krbhst_info* calloc (int,int) ; 
 int getaddrinfo (char*,char*,struct addrinfo*,struct addrinfo**) ; 
 int getnameinfo (struct sockaddr*,int /*<<< orphan*/ ,char*,int,char*,int,int) ; 
 int /*<<< orphan*/  krbhst_get_default_proto (struct krb5_krbhst_data*) ; 
 int /*<<< orphan*/  make_hints (struct addrinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int /*<<< orphan*/  socket_get_port (struct sockaddr*) ; 
 int /*<<< orphan*/  socket_sockaddr_size (struct sockaddr*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static krb5_error_code
add_locate(void *ctx, int type, struct sockaddr *addr)
{
    struct krb5_krbhst_info *hi;
    struct krb5_krbhst_data *kd = ctx;
    char host[NI_MAXHOST], port[NI_MAXSERV];
    struct addrinfo hints, *ai;
    socklen_t socklen;
    size_t hostlen;
    int ret;

    socklen = socket_sockaddr_size(addr);

    ret = getnameinfo(addr, socklen, host, sizeof(host), port, sizeof(port),
		      NI_NUMERICHOST|NI_NUMERICSERV);
    if (ret != 0)
	return 0;

    make_hints(&hints, krbhst_get_default_proto(kd));
    ret = getaddrinfo(host, port, &hints, &ai);
    if (ret)
	return 0;

    hostlen = strlen(host);

    hi = calloc(1, sizeof(*hi) + hostlen);
    if(hi == NULL)
	return ENOMEM;

    hi->proto = krbhst_get_default_proto(kd);
    hi->port  = hi->def_port = socket_get_port(addr);
    hi->ai    = ai;
    memmove(hi->hostname, host, hostlen);
    hi->hostname[hostlen] = '\0';
    append_host_hostinfo(kd, hi);

    return 0;
}