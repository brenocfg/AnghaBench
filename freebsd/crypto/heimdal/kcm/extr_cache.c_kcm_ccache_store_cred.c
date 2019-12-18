#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_1__* kcm_ccache ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCM_ASSERT_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  kcm_ccache_store_cred_internal (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 

krb5_error_code
kcm_ccache_store_cred(krb5_context context,
		      kcm_ccache ccache,
		      krb5_creds *creds,
		      int copy)
{
    krb5_error_code ret;
    krb5_creds *tmp;

    KCM_ASSERT_VALID(ccache);

    HEIMDAL_MUTEX_lock(&ccache->mutex);
    ret = kcm_ccache_store_cred_internal(context, ccache, creds, copy, &tmp);
    HEIMDAL_MUTEX_unlock(&ccache->mutex);

    return ret;
}