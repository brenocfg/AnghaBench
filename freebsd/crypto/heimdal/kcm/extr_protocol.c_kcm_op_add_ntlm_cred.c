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
struct kcm_ntlm_cred {int /*<<< orphan*/  uuid; int /*<<< orphan*/  session; int /*<<< orphan*/  uid; struct kcm_ntlm_cred* next; int /*<<< orphan*/  nthash; int /*<<< orphan*/  domain; int /*<<< orphan*/  user; } ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  kcm_operation ;
struct TYPE_4__ {int /*<<< orphan*/  session; int /*<<< orphan*/  uid; } ;
typedef  TYPE_1__ kcm_client ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  RAND_bytes (int /*<<< orphan*/ ,int) ; 
 struct kcm_ntlm_cred* calloc (int,int) ; 
 struct kcm_ntlm_cred* find_ntlm_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  free_cred (struct kcm_ntlm_cred*) ; 
 scalar_t__ krb5_ret_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_ret_stringz (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_storage_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct kcm_ntlm_cred* ntlm_head ; 

__attribute__((used)) static krb5_error_code
kcm_op_add_ntlm_cred(krb5_context context,
		     kcm_client *client,
		     kcm_operation opcode,
		     krb5_storage *request,
		     krb5_storage *response)
{
    struct kcm_ntlm_cred *cred, *c;
    krb5_error_code ret;

    cred = calloc(1, sizeof(*cred));
    if (cred == NULL)
	return ENOMEM;

    RAND_bytes(cred->uuid, sizeof(cred->uuid));

    ret = krb5_ret_stringz(request, &cred->user);
    if (ret)
	goto error;

    ret = krb5_ret_stringz(request, &cred->domain);
    if (ret)
	goto error;

    ret = krb5_ret_data(request, &cred->nthash);
    if (ret)
	goto error;

    /* search for dups */
    c = find_ntlm_cred(cred->user, cred->domain, client);
    if (c) {
	krb5_data hash = c->nthash;
	c->nthash = cred->nthash;
	cred->nthash = hash;
	free_cred(cred);
	cred = c;
    } else {
	cred->next = ntlm_head;
	ntlm_head = cred;
    }

    cred->uid = client->uid;
    cred->session = client->session;

    /* write response */
    (void)krb5_storage_write(response, &cred->uuid, sizeof(cred->uuid));

    return 0;

 error:
    free_cred(cred);

    return ret;
}