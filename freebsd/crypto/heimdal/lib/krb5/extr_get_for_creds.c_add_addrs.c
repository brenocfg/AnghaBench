#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct addrinfo {int /*<<< orphan*/  ai_addr; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_10__ {unsigned int len; TYPE_2__* val; } ;
typedef  TYPE_1__ krb5_addresses ;
struct TYPE_11__ {int /*<<< orphan*/  address; scalar_t__ addr_type; } ;
typedef  TYPE_2__ krb5_address ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  KRB5_PROG_ATYPE_NOSUPP ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 scalar_t__ krb5_address_search (int /*<<< orphan*/ ,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_clear_error_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_data_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_address (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_free_addresses (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_sockaddr2address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 void* realloc (TYPE_2__*,unsigned int) ; 

__attribute__((used)) static krb5_error_code
add_addrs(krb5_context context,
	  krb5_addresses *addr,
	  struct addrinfo *ai)
{
    krb5_error_code ret;
    unsigned n, i;
    void *tmp;
    struct addrinfo *a;

    n = 0;
    for (a = ai; a != NULL; a = a->ai_next)
	++n;

    tmp = realloc(addr->val, (addr->len + n) * sizeof(*addr->val));
    if (tmp == NULL && (addr->len + n) != 0) {
	ret = ENOMEM;
	krb5_set_error_message(context, ret, N_("malloc: out of memory", ""));
	goto fail;
    }
    addr->val = tmp;
    for (i = addr->len; i < (addr->len + n); ++i) {
	addr->val[i].addr_type = 0;
	krb5_data_zero(&addr->val[i].address);
    }
    i = addr->len;
    for (a = ai; a != NULL; a = a->ai_next) {
	krb5_address ad;

	ret = krb5_sockaddr2address (context, a->ai_addr, &ad);
	if (ret == 0) {
	    if (krb5_address_search(context, &ad, addr))
		krb5_free_address(context, &ad);
	    else
		addr->val[i++] = ad;
	}
	else if (ret == KRB5_PROG_ATYPE_NOSUPP)
	    krb5_clear_error_message (context);
	else
	    goto fail;
	addr->len = i;
    }
    return 0;
fail:
    krb5_free_addresses (context, addr);
    return ret;
}