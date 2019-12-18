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
struct kcm_ntlm_cred {struct kcm_ntlm_cred* next; int /*<<< orphan*/  session; int /*<<< orphan*/  uid; int /*<<< orphan*/  domain; int /*<<< orphan*/  user; } ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  kcm_operation ;
typedef  int /*<<< orphan*/  kcm_client ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_cred (struct kcm_ntlm_cred*) ; 
 scalar_t__ kcm_is_same_session (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_ret_stringz (int /*<<< orphan*/ *,char**) ; 
 struct kcm_ntlm_cred* ntlm_head ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static krb5_error_code
kcm_op_del_ntlm_cred(krb5_context context,
		     kcm_client *client,
		     kcm_operation opcode,
		     krb5_storage *request,
		     krb5_storage *response)
{
    struct kcm_ntlm_cred **cp, *c;
    char *user = NULL, *domain = NULL;
    krb5_error_code ret;

    ret = krb5_ret_stringz(request, &user);
    if (ret)
	goto error;

    ret = krb5_ret_stringz(request, &domain);
    if (ret)
	goto error;

    for (cp = &ntlm_head; *cp != NULL; cp = &(*cp)->next) {
	if (strcmp(user, (*cp)->user) == 0 && strcmp(domain, (*cp)->domain) == 0 &&
	    kcm_is_same_session(client, (*cp)->uid, (*cp)->session))
	{
	    c = *cp;
	    *cp = c->next;

	    free_cred(c);
	    break;
	}
    }

 error:
    free(user);
    free(domain);

    return ret;
}