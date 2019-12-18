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
struct kcm_default_cache {void* name; struct kcm_default_cache* next; int /*<<< orphan*/  uid; int /*<<< orphan*/  session; } ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  kcm_operation ;
struct TYPE_5__ {int /*<<< orphan*/  uid; int /*<<< orphan*/  session; } ;
typedef  TYPE_1__ kcm_client ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  KCM_LOG_REQUEST_NAME (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 struct kcm_default_cache* default_caches ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ kcm_is_same_session (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_ret_stringz (int /*<<< orphan*/ *,char**) ; 
 struct kcm_default_cache* malloc (int) ; 
 void* strdup (char*) ; 

__attribute__((used)) static krb5_error_code
kcm_op_set_default_cache(krb5_context context,
			 kcm_client *client,
			 kcm_operation opcode,
			 krb5_storage *request,
			 krb5_storage *response)
{
    struct kcm_default_cache *c;
    krb5_error_code ret;
    char *name;

    ret = krb5_ret_stringz(request, &name);
    if (ret)
	return ret;

    KCM_LOG_REQUEST_NAME(context, client, opcode, name);

    for (c = default_caches; c != NULL; c = c->next) {
	if (kcm_is_same_session(client, c->uid, c->session))
	    break;
    }
    if (c == NULL) {
	c = malloc(sizeof(*c));
	if (c == NULL)
	    return ENOMEM;
	c->session = client->session;
	c->uid = client->uid;
	c->name = strdup(name);

	c->next = default_caches;
	default_caches = c;
    } else {
	free(c->name);
	c->name = strdup(name);
    }

    return 0;
}