#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_1__* kcm_ccache ;
struct TYPE_6__ {int refcnt; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCM_ASSERT_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  kcm_free_ccache_data_internal (int /*<<< orphan*/ ,TYPE_1__*) ; 

krb5_error_code
kcm_release_ccache(krb5_context context, kcm_ccache c)
{
    krb5_error_code ret = 0;

    KCM_ASSERT_VALID(c);

    HEIMDAL_MUTEX_lock(&c->mutex);
    if (c->refcnt == 1) {
	kcm_free_ccache_data_internal(context, c);
	free(c);
    } else {
	c->refcnt--;
	HEIMDAL_MUTEX_unlock(&c->mutex);
    }

    return ret;
}