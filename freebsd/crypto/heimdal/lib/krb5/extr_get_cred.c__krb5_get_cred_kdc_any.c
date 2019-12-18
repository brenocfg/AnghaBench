#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_principal ;
struct TYPE_11__ {scalar_t__ canonicalize; } ;
struct TYPE_12__ {TYPE_1__ b; } ;
typedef  TYPE_2__ krb5_kdc_flags ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_deltat ;
typedef  int /*<<< orphan*/  krb5_creds ;
typedef  TYPE_3__* krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  int /*<<< orphan*/  Ticket ;
struct TYPE_13__ {scalar_t__ kdc_usec_offset; int /*<<< orphan*/  kdc_sec_offset; } ;

/* Variables and functions */
 scalar_t__ get_cred_kdc_capath (TYPE_3__*,TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ***) ; 
 scalar_t__ get_cred_kdc_referral (TYPE_3__*,TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ***) ; 
 scalar_t__ krb5_cc_get_kdc_offset (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

krb5_error_code
_krb5_get_cred_kdc_any(krb5_context context,
		       krb5_kdc_flags flags,
		       krb5_ccache ccache,
		       krb5_creds *in_creds,
		       krb5_principal impersonate_principal,
		       Ticket *second_ticket,
		       krb5_creds **out_creds,
		       krb5_creds ***ret_tgts)
{
    krb5_error_code ret;
    krb5_deltat offset;

    ret = krb5_cc_get_kdc_offset(context, ccache, &offset);
    if (ret) {
	context->kdc_sec_offset = offset;
	context->kdc_usec_offset = 0;
    }

    ret = get_cred_kdc_referral(context,
				flags,
				ccache,
				in_creds,
				impersonate_principal,
				second_ticket,
				out_creds,
				ret_tgts);
    if (ret == 0 || flags.b.canonicalize)
	return ret;
    return get_cred_kdc_capath(context,
				flags,
				ccache,
				in_creds,
				impersonate_principal,
				second_ticket,
				out_creds,
				ret_tgts);
}