#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  scalar_t__ kadm5_ret_t ;
struct TYPE_3__ {int /*<<< orphan*/  ac; int /*<<< orphan*/  context; int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ kadm5_client_context ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 scalar_t__ KADM5_RPC_ERROR ; 
 scalar_t__ KRB5_CC_END ; 
 int /*<<< orphan*/  krb5_clear_error_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_data_free (int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_rd_priv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_ret_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_from_fd (int /*<<< orphan*/ ) ; 

kadm5_ret_t
_kadm5_client_recv(kadm5_client_context *context, krb5_data *reply)
{
    krb5_error_code ret;
    krb5_data data;
    krb5_storage *sock;

    sock = krb5_storage_from_fd(context->sock);
    if(sock == NULL) {
	krb5_clear_error_message(context->context);
	return ENOMEM;
    }
    ret = krb5_ret_data(sock, &data);
    krb5_storage_free(sock);
    krb5_clear_error_message(context->context);
    if(ret == KRB5_CC_END)
	return KADM5_RPC_ERROR;
    else if(ret)
	return ret;

    ret = krb5_rd_priv(context->context, context->ac, &data, reply, NULL);
    krb5_data_free(&data);
    return ret;
}