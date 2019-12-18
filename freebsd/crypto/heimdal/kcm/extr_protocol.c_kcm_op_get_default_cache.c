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
struct kcm_default_cache {char* name; int /*<<< orphan*/  session; int /*<<< orphan*/  uid; struct kcm_default_cache* next; } ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  kcm_operation ;
struct TYPE_6__ {scalar_t__ uid; } ;
typedef  TYPE_1__ kcm_client ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  KCM_LOG_REQUEST (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asprintf (char**,char*,int) ; 
 struct kcm_default_cache* default_caches ; 
 int /*<<< orphan*/  free (char*) ; 
 char* kcm_ccache_first_name (TYPE_1__*) ; 
 scalar_t__ kcm_is_same_session (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_store_stringz (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static krb5_error_code
kcm_op_get_default_cache(krb5_context context,
			 kcm_client *client,
			 kcm_operation opcode,
			 krb5_storage *request,
			 krb5_storage *response)
{
    struct kcm_default_cache *c;
    krb5_error_code ret;
    const char *name = NULL;
    char *n = NULL;

    KCM_LOG_REQUEST(context, client, opcode);

    for (c = default_caches; c != NULL; c = c->next) {
	if (kcm_is_same_session(client, c->uid, c->session)) {
	    name = c->name;
	    break;
	}
    }
    if (name == NULL)
	name = n = kcm_ccache_first_name(client);

    if (name == NULL) {
	asprintf(&n, "%d", (int)client->uid);
	name = n;
    }
    if (name == NULL)
	return ENOMEM;
    ret = krb5_store_stringz(response, name);
    if (n)
	free(n);
    return ret;
}