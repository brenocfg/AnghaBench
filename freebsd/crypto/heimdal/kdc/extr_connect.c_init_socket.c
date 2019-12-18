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
struct sockaddr {int sa_family; } ;
struct descr {int type; int port; void* s; } ;
typedef  int /*<<< orphan*/  one ;
typedef  int krb5_socklen_t ;
typedef  int /*<<< orphan*/  krb5_kdc_configuration ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_address ;
typedef  int /*<<< orphan*/  a_str ;
typedef  int /*<<< orphan*/  __ss ;

/* Variables and functions */
 int SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SOMAXCONN ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  bind (void*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  init_descr (struct descr*) ; 
 scalar_t__ krb5_addr2sockaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sockaddr*,int*,int) ; 
 int /*<<< orphan*/  krb5_print_address (int /*<<< orphan*/ *,char*,int,size_t*) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  listen (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int) ; 
 void* rk_INVALID_SOCKET ; 
 scalar_t__ rk_IS_BAD_SOCKET (void*) ; 
 scalar_t__ rk_IS_SOCKET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_closesocket (void*) ; 
 int /*<<< orphan*/  setsockopt (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 void* socket (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
init_socket(krb5_context context,
	    krb5_kdc_configuration *config,
	    struct descr *d, krb5_address *a, int family, int type, int port)
{
    krb5_error_code ret;
    struct sockaddr_storage __ss;
    struct sockaddr *sa = (struct sockaddr *)&__ss;
    krb5_socklen_t sa_size = sizeof(__ss);

    init_descr (d);

    ret = krb5_addr2sockaddr (context, a, sa, &sa_size, port);
    if (ret) {
	krb5_warn(context, ret, "krb5_addr2sockaddr");
	rk_closesocket(d->s);
	d->s = rk_INVALID_SOCKET;
	return;
    }

    if (sa->sa_family != family)
	return;

    d->s = socket(family, type, 0);
    if(rk_IS_BAD_SOCKET(d->s)){
	krb5_warn(context, errno, "socket(%d, %d, 0)", family, type);
	d->s = rk_INVALID_SOCKET;
	return;
    }
#if defined(HAVE_SETSOCKOPT) && defined(SOL_SOCKET) && defined(SO_REUSEADDR)
    {
	int one = 1;
	setsockopt(d->s, SOL_SOCKET, SO_REUSEADDR, (void *)&one, sizeof(one));
    }
#endif
    d->type = type;
    d->port = port;

    if(rk_IS_SOCKET_ERROR(bind(d->s, sa, sa_size))){
	char a_str[256];
	size_t len;

	krb5_print_address (a, a_str, sizeof(a_str), &len);
	krb5_warn(context, errno, "bind %s/%d", a_str, ntohs(port));
	rk_closesocket(d->s);
	d->s = rk_INVALID_SOCKET;
	return;
    }
    if(type == SOCK_STREAM && rk_IS_SOCKET_ERROR(listen(d->s, SOMAXCONN))){
	char a_str[256];
	size_t len;

	krb5_print_address (a, a_str, sizeof(a_str), &len);
	krb5_warn(context, errno, "listen %s/%d", a_str, ntohs(port));
	rk_closesocket(d->s);
	d->s = rk_INVALID_SOCKET;
	return;
    }
}