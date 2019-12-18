#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  kcm_operation ;
struct TYPE_6__ {int fire_time; TYPE_2__* ccache; int /*<<< orphan*/  action; scalar_t__ backoff_time; scalar_t__ expire_time; } ;
typedef  TYPE_1__ kcm_event ;
typedef  int /*<<< orphan*/  kcm_client ;
typedef  TYPE_2__* kcm_ccache ;
struct TYPE_7__ {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  KCM_EVENT_DESTROY_EMPTY_CACHE ; 
 int /*<<< orphan*/  KCM_LOG_REQUEST (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ kcm_ccache_new_client (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,TYPE_2__**) ; 
 scalar_t__ kcm_enqueue_event_relative (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  kcm_release_ccache (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_ret_principal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_ret_stringz (int /*<<< orphan*/ *,char**) ; 

__attribute__((used)) static krb5_error_code
kcm_op_initialize(krb5_context context,
		  kcm_client *client,
		  kcm_operation opcode,
		  krb5_storage *request,
		  krb5_storage *response)
{
    kcm_ccache ccache;
    krb5_principal principal;
    krb5_error_code ret;
    char *name;
#if 0
    kcm_event event;
#endif

    KCM_LOG_REQUEST(context, client, opcode);

    ret = krb5_ret_stringz(request, &name);
    if (ret)
	return ret;

    ret = krb5_ret_principal(request, &principal);
    if (ret) {
	free(name);
	return ret;
    }

    ret = kcm_ccache_new_client(context, client, name, &ccache);
    if (ret) {
	free(name);
	krb5_free_principal(context, principal);
	return ret;
    }

    ccache->client = principal;

    free(name);

#if 0
    /*
     * Create a new credentials cache. To mitigate DoS attacks we will
     * expire it in 30 minutes unless it has some credentials added
     * to it
     */

    event.fire_time = 30 * 60;
    event.expire_time = 0;
    event.backoff_time = 0;
    event.action = KCM_EVENT_DESTROY_EMPTY_CACHE;
    event.ccache = ccache;

    ret = kcm_enqueue_event_relative(context, &event);
#endif

    kcm_release_ccache(context, ccache);

    return ret;
}