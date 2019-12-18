#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int service; } ;
struct svc_rpc_gss_client {int /*<<< orphan*/  cl_rpcflavor; TYPE_1__ cl_rawcred; int /*<<< orphan*/  cl_mech; } ;
struct TYPE_5__ {int member_0; void* member_1; } ;
typedef  TYPE_2__ gss_OID_desc ;

/* Variables and functions */
 int /*<<< orphan*/  RPCSEC_GSS ; 
 int /*<<< orphan*/  RPCSEC_GSS_KRB5 ; 
 int /*<<< orphan*/  RPCSEC_GSS_KRB5I ; 
 int /*<<< orphan*/  RPCSEC_GSS_KRB5P ; 
 scalar_t__ kgss_oid_equal (int /*<<< orphan*/ ,TYPE_2__*) ; 
#define  rpc_gss_svc_default 131 
#define  rpc_gss_svc_integrity 130 
#define  rpc_gss_svc_none 129 
#define  rpc_gss_svc_privacy 128 

__attribute__((used)) static void
svc_rpc_gss_set_flavor(struct svc_rpc_gss_client *client)
{
	static gss_OID_desc krb5_mech_oid =
		{9, (void *) "\x2a\x86\x48\x86\xf7\x12\x01\x02\x02" };

	/*
	 * Attempt to translate mech type and service into a
	 * 'pseudo flavor'. Hardwire in krb5 support for now.
	 */
	if (kgss_oid_equal(client->cl_mech, &krb5_mech_oid)) {
		switch (client->cl_rawcred.service) {
		case rpc_gss_svc_default:
		case rpc_gss_svc_none:
			client->cl_rpcflavor = RPCSEC_GSS_KRB5;
			break;
		case rpc_gss_svc_integrity:
			client->cl_rpcflavor = RPCSEC_GSS_KRB5I;
			break;
		case rpc_gss_svc_privacy:
			client->cl_rpcflavor = RPCSEC_GSS_KRB5P;
			break;
		}
	} else {
		client->cl_rpcflavor = RPCSEC_GSS;
	}
}