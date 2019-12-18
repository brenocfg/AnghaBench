#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  kcm_operation ;
typedef  int /*<<< orphan*/  kcm_client ;
typedef  TYPE_1__* kcm_ccache ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  uuid; struct TYPE_4__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int KCM_FLAGS_VALID ; 
 scalar_t__ KRB5_FCC_NOFILE ; 
 TYPE_1__* ccache_head ; 
 int /*<<< orphan*/  ccache_mutex ; 
 scalar_t__ kcm_access (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_storage_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

krb5_error_code
kcm_ccache_get_uuids(krb5_context context, kcm_client *client, kcm_operation opcode, krb5_storage *sp)
{
    krb5_error_code ret;
    kcm_ccache p;

    ret = KRB5_FCC_NOFILE;

    HEIMDAL_MUTEX_lock(&ccache_mutex);

    for (p = ccache_head; p != NULL; p = p->next) {
	if ((p->flags & KCM_FLAGS_VALID) == 0)
	    continue;
	ret = kcm_access(context, client, opcode, p);
	if (ret) {
	    ret = 0;
	    continue;
	}
	krb5_storage_write(sp, p->uuid, sizeof(p->uuid));
    }

    HEIMDAL_MUTEX_unlock(&ccache_mutex);

    return ret;
}