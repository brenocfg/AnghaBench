#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_9__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ krb5_data ;
typedef  scalar_t__ kadm5_ret_t ;
struct TYPE_10__ {int sock; int /*<<< orphan*/  context; int /*<<< orphan*/  ac; } ;
typedef  TYPE_2__ kadm5_client_context ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  krb5_clear_error_message (int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_data_alloc (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_1__*) ; 
 scalar_t__ krb5_mk_priv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_from_fd (int) ; 
 int /*<<< orphan*/  krb5_storage_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t krb5_storage_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_store_data (int /*<<< orphan*/ *,TYPE_1__) ; 

kadm5_ret_t
_kadm5_client_send(kadm5_client_context *context, krb5_storage *sp)
{
    krb5_data msg, out;
    krb5_error_code ret;
    size_t len;
    krb5_storage *sock;

    assert(context->sock != -1);

    len = krb5_storage_seek(sp, 0, SEEK_CUR);
    ret = krb5_data_alloc(&msg, len);
    if (ret) {
	krb5_clear_error_message(context->context);
	return ret;
    }
    krb5_storage_seek(sp, 0, SEEK_SET);
    krb5_storage_read(sp, msg.data, msg.length);

    ret = krb5_mk_priv(context->context, context->ac, &msg, &out, NULL);
    krb5_data_free(&msg);
    if(ret)
	return ret;

    sock = krb5_storage_from_fd(context->sock);
    if(sock == NULL) {
	krb5_clear_error_message(context->context);
	krb5_data_free(&out);
	return ENOMEM;
    }

    ret = krb5_store_data(sock, out);
    if (ret)
	krb5_clear_error_message(context->context);
    krb5_storage_free(sock);
    krb5_data_free(&out);
    return ret;
}