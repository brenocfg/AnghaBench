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
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_1__* kcm_ccache ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCM_ASSERT_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  kcm_ccache_remove_creds_internal (int /*<<< orphan*/ ,TYPE_1__*) ; 

krb5_error_code
kcm_ccache_remove_creds(krb5_context context,
			kcm_ccache ccache)
{
    krb5_error_code ret;

    KCM_ASSERT_VALID(ccache);

    HEIMDAL_MUTEX_lock(&ccache->mutex);
    ret = kcm_ccache_remove_creds_internal(context, ccache);
    HEIMDAL_MUTEX_unlock(&ccache->mutex);

    return ret;
}