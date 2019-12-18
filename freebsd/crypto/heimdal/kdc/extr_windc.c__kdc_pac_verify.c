#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int /*<<< orphan*/  krb5_pac ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  hdb_entry_ex ;
struct TYPE_2__ {scalar_t__ (* pac_verify ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  windcctx ; 
 TYPE_1__* windcft ; 

krb5_error_code
_kdc_pac_verify(krb5_context context,
		const krb5_principal client_principal,
		const krb5_principal delegated_proxy_principal,
		hdb_entry_ex *client,
		hdb_entry_ex *server,
		hdb_entry_ex *krbtgt,
		krb5_pac *pac,
		int *verified)
{
    krb5_error_code ret;

    if (windcft == NULL)
	return 0;

    ret = windcft->pac_verify(windcctx, context,
			      client_principal,
			      delegated_proxy_principal,
			      client, server, krbtgt, pac);
    if (ret == 0)
	*verified = 1;
    return ret;
}