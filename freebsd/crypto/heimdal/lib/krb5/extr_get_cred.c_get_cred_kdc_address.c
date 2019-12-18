#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int /*<<< orphan*/  krb5_kdc_flags ;
typedef  int /*<<< orphan*/  krb5_error_code ;
struct TYPE_15__ {scalar_t__ len; } ;
struct TYPE_17__ {TYPE_2__* server; TYPE_1__ addresses; } ;
typedef  TYPE_3__ krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  int /*<<< orphan*/  krb5_boolean ;
struct TYPE_18__ {scalar_t__ len; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ krb5_addresses ;
typedef  int /*<<< orphan*/  Ticket ;
struct TYPE_16__ {int /*<<< orphan*/  realm; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  get_cred_kdc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  krb5_appdefault_boolean (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_addresses (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  krb5_get_all_client_addrs (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static krb5_error_code
get_cred_kdc_address(krb5_context context,
		     krb5_ccache id,
		     krb5_kdc_flags flags,
		     krb5_addresses *addrs,
		     krb5_creds *in_creds,
		     krb5_creds *krbtgt,
		     krb5_principal impersonate_principal,
		     Ticket *second_ticket,
		     krb5_creds *out_creds)
{
    krb5_error_code ret;
    krb5_addresses addresses = { 0, NULL };

    /*
     * Inherit the address-ness of the krbtgt if the address is not
     * specified.
     */

    if (addrs == NULL && krbtgt->addresses.len != 0) {
	krb5_boolean noaddr;

	krb5_appdefault_boolean(context, NULL, krbtgt->server->realm,
				"no-addresses", FALSE, &noaddr);

	if (!noaddr) {
	    krb5_get_all_client_addrs(context, &addresses);
	    /* XXX this sucks. */
	    addrs = &addresses;
	    if(addresses.len == 0)
		addrs = NULL;
	}
    }
    ret = get_cred_kdc(context, id, flags, addrs, in_creds,
		       krbtgt, impersonate_principal,
		       second_ticket, out_creds);
    krb5_free_addresses(context, &addresses);
    return ret;
}