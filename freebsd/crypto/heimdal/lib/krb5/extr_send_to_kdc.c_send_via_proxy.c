#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct addrinfo {int ai_socktype; int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  portstr ;
typedef  scalar_t__ krb5_socket_t ;
struct TYPE_10__ {int /*<<< orphan*/  hostname; } ;
typedef  TYPE_1__ krb5_krbhst_info ;
struct TYPE_11__ {scalar_t__ length; } ;
typedef  TYPE_2__ krb5_data ;
typedef  TYPE_3__* krb5_context ;
typedef  int /*<<< orphan*/  hints ;
struct TYPE_12__ {int /*<<< orphan*/  kdc_timeout; int /*<<< orphan*/  http_proxy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int NI_MAXSERV ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
 int SOCK_CLOEXEC ; 
 int SOCK_STREAM ; 
 int asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 scalar_t__ connect (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int getaddrinfo (char*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  init_port (char*,int /*<<< orphan*/ ) ; 
 int krb5_eai_to_heim_errno (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ rk_INVALID_SOCKET ; 
 int /*<<< orphan*/  rk_cloexec (scalar_t__) ; 
 int /*<<< orphan*/  rk_closesocket (scalar_t__) ; 
 int send_and_recv_http (scalar_t__,int /*<<< orphan*/ ,char*,TYPE_2__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
send_via_proxy (krb5_context context,
		const krb5_krbhst_info *hi,
		const krb5_data *send_data,
		krb5_data *receive)
{
    char *proxy2 = strdup(context->http_proxy);
    char *proxy  = proxy2;
    char *prefix = NULL;
    char *colon;
    struct addrinfo hints;
    struct addrinfo *ai, *a;
    int ret;
    krb5_socket_t s = rk_INVALID_SOCKET;
    char portstr[NI_MAXSERV];

    if (proxy == NULL)
	return ENOMEM;
    if (strncmp (proxy, "http://", 7) == 0)
	proxy += 7;

    colon = strchr(proxy, ':');
    if(colon != NULL)
	*colon++ = '\0';
    memset (&hints, 0, sizeof(hints));
    hints.ai_family   = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    snprintf (portstr, sizeof(portstr), "%d",
	      ntohs(init_port (colon, htons(80))));
    ret = getaddrinfo (proxy, portstr, &hints, &ai);
    free (proxy2);
    if (ret)
	return krb5_eai_to_heim_errno(ret, errno);

    for (a = ai; a != NULL; a = a->ai_next) {
	s = socket (a->ai_family, a->ai_socktype | SOCK_CLOEXEC, a->ai_protocol);
	if (s < 0)
	    continue;
	rk_cloexec(s);
	if (connect (s, a->ai_addr, a->ai_addrlen) < 0) {
	    rk_closesocket (s);
	    continue;
	}
	break;
    }
    if (a == NULL) {
	freeaddrinfo (ai);
	return 1;
    }
    freeaddrinfo (ai);

    ret = asprintf(&prefix, "http://%s/", hi->hostname);
    if(ret < 0 || prefix == NULL) {
	close(s);
	return 1;
    }
    ret = send_and_recv_http(s, context->kdc_timeout,
			     prefix, send_data, receive);
    rk_closesocket (s);
    free(prefix);
    if(ret == 0 && receive->length != 0)
	return 0;
    return 1;
}