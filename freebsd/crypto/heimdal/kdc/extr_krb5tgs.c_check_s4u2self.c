#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_kdc_configuration ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_const_principal ;
struct TYPE_8__ {int /*<<< orphan*/  principal; } ;
struct TYPE_9__ {TYPE_1__ entry; } ;
typedef  TYPE_2__ hdb_entry_ex ;
struct TYPE_10__ {scalar_t__ (* hdb_check_s4u2self ) (int /*<<< orphan*/ ,TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ HDB ;

/* Variables and functions */
 scalar_t__ KRB5KDC_ERR_BADOPTION ; 
 scalar_t__ TRUE ; 
 scalar_t__ krb5_principal_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static krb5_error_code
check_s4u2self(krb5_context context,
	       krb5_kdc_configuration *config,
	       HDB *clientdb,
	       hdb_entry_ex *client,
	       krb5_const_principal server)
{
    krb5_error_code ret;

    /* if client does a s4u2self to itself, that ok */
    if (krb5_principal_compare(context, client->entry.principal, server) == TRUE)
	return 0;

    if (clientdb->hdb_check_s4u2self) {
	ret = clientdb->hdb_check_s4u2self(context, clientdb, client, server);
	if (ret == 0)
	    return 0;
    } else {
	ret = KRB5KDC_ERR_BADOPTION;
    }
    return ret;
}