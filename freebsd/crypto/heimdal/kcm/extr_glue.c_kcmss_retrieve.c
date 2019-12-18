#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_flags ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  int /*<<< orphan*/  kcm_ccache ;

/* Variables and functions */
 int /*<<< orphan*/  KCMCACHE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KCM_ASSERT_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ kcm_ccache_retrieve_cred_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ **) ; 
 scalar_t__ krb5_copy_creds_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static krb5_error_code
kcmss_retrieve(krb5_context context,
	       krb5_ccache id,
	       krb5_flags which,
	       const krb5_creds *mcred,
	       krb5_creds *creds)
{
    krb5_error_code ret;
    kcm_ccache c = KCMCACHE(id);
    krb5_creds *credp;

    KCM_ASSERT_VALID(c);

    ret = kcm_ccache_retrieve_cred_internal(context, c, which,
					    mcred, &credp);
    if (ret)
	return ret;

    ret = krb5_copy_creds_contents(context, credp, creds);
    if (ret)
	return ret;

    return 0;
}