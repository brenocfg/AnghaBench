#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct descr {scalar_t__ s; } ;
typedef  int /*<<< orphan*/  krb5_kdc_configuration ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_6__ {int len; int /*<<< orphan*/ * val; } ;
typedef  TYPE_1__ krb5_addresses ;
typedef  int /*<<< orphan*/  a_str ;
struct TYPE_7__ {scalar_t__ type; int /*<<< orphan*/  port; int /*<<< orphan*/  family; } ;

/* Variables and functions */
 scalar_t__ SOCK_STREAM ; 
 TYPE_1__ explicit_addresses ; 
 int /*<<< orphan*/  init_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct descr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdc_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*,unsigned long) ; 
 int /*<<< orphan*/  krb5_free_addresses (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ krb5_get_all_server_addrs (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_print_address (int /*<<< orphan*/ *,char*,int,size_t*) ; 
 struct descr* malloc (int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int num_ports ; 
 int /*<<< orphan*/  parse_ports (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_str ; 
 TYPE_2__* ports ; 
 struct descr* realloc (struct descr*,int) ; 
 int /*<<< orphan*/  reinit_descrs (struct descr*,int) ; 
 scalar_t__ rk_INVALID_SOCKET ; 

__attribute__((used)) static int
init_sockets(krb5_context context,
	     krb5_kdc_configuration *config,
	     struct descr **desc)
{
    krb5_error_code ret;
    size_t i, j;
    struct descr *d;
    int num = 0;
    krb5_addresses addresses;

    if (explicit_addresses.len) {
	addresses = explicit_addresses;
    } else {
	ret = krb5_get_all_server_addrs (context, &addresses);
	if (ret)
	    krb5_err (context, 1, ret, "krb5_get_all_server_addrs");
    }
    parse_ports(context, config, port_str);
    d = malloc(addresses.len * num_ports * sizeof(*d));
    if (d == NULL)
	krb5_errx(context, 1, "malloc(%lu) failed",
		  (unsigned long)num_ports * sizeof(*d));

    for (i = 0; i < num_ports; i++){
	for (j = 0; j < addresses.len; ++j) {
	    init_socket(context, config, &d[num], &addresses.val[j],
			ports[i].family, ports[i].type, ports[i].port);
	    if(d[num].s != rk_INVALID_SOCKET){
		char a_str[80];
		size_t len;

		krb5_print_address (&addresses.val[j], a_str,
				    sizeof(a_str), &len);

		kdc_log(context, config, 5, "listening on %s port %u/%s",
			a_str,
			ntohs(ports[i].port),
			(ports[i].type == SOCK_STREAM) ? "tcp" : "udp");
		/* XXX */
		num++;
	    }
	}
    }
    krb5_free_addresses (context, &addresses);
    d = realloc(d, num * sizeof(*d));
    if (d == NULL && num != 0)
	krb5_errx(context, 1, "realloc(%lu) failed",
		  (unsigned long)num * sizeof(*d));
    reinit_descrs (d, num);
    *desc = d;
    return num;
}