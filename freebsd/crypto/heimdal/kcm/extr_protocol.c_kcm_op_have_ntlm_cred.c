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
struct kcm_ntlm_cred {int dummy; } ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  kcm_operation ;
typedef  int /*<<< orphan*/  kcm_client ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 struct kcm_ntlm_cred* find_ntlm_cred (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ krb5_ret_stringz (int /*<<< orphan*/ *,char**) ; 

__attribute__((used)) static krb5_error_code
kcm_op_have_ntlm_cred(krb5_context context,
		     kcm_client *client,
		     kcm_operation opcode,
		     krb5_storage *request,
		     krb5_storage *response)
{
    struct kcm_ntlm_cred *c;
    char *user = NULL, *domain = NULL;
    krb5_error_code ret;

    ret = krb5_ret_stringz(request, &user);
    if (ret)
	goto error;

    ret = krb5_ret_stringz(request, &domain);
    if (ret)
	goto error;

    if (domain[0] == '\0') {
	free(domain);
	domain = NULL;
    }

    c = find_ntlm_cred(user, domain, client);
    if (c == NULL)
	ret = ENOENT;

 error:
    free(user);
    if (domain)
	free(domain);

    return ret;
}