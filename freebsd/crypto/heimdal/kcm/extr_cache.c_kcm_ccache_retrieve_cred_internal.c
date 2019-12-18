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
struct kcm_creds {int /*<<< orphan*/  cred; struct kcm_creds* next; } ;
typedef  int /*<<< orphan*/  krb5_flags ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  scalar_t__ krb5_boolean ;
typedef  TYPE_1__* kcm_ccache ;
struct TYPE_3__ {struct kcm_creds* creds; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ KRB5_CC_END ; 
 scalar_t__ krb5_compare_creds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 

krb5_error_code
kcm_ccache_retrieve_cred_internal(krb5_context context,
			 	  kcm_ccache ccache,
			 	  krb5_flags whichfields,
			 	  const krb5_creds *mcreds,
			 	  krb5_creds **creds)
{
    krb5_boolean match;
    struct kcm_creds *c;
    krb5_error_code ret;

    memset(creds, 0, sizeof(*creds));

    ret = KRB5_CC_END;

    match = FALSE;
    for (c = ccache->creds; c != NULL; c = c->next) {
	match = krb5_compare_creds(context, whichfields, mcreds, &c->cred);
	if (match)
	    break;
    }

    if (match) {
	ret = 0;
	*creds = &c->cred;
    }

    return ret;
}