#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; scalar_t__ ap_req_nofail; } ;
typedef  TYPE_1__ krb5_verify_init_creds_opt ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int KRB5_VERIFY_INIT_CREDS_OPT_AP_REQ_NOFAIL ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ krb5_config_get_bool (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static krb5_boolean
fail_verify_is_ok (krb5_context context,
		   krb5_verify_init_creds_opt *options)
{
    if ((options->flags & KRB5_VERIFY_INIT_CREDS_OPT_AP_REQ_NOFAIL
	 && options->ap_req_nofail != 0)
	|| krb5_config_get_bool (context,
				 NULL,
				 "libdefaults",
				 "verify_ap_req_nofail",
				 NULL))
	return FALSE;
    else
	return TRUE;
}