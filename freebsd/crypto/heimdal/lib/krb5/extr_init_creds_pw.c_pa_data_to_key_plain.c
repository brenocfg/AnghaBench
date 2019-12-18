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
typedef  int /*<<< orphan*/  krb5_salt ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
struct TYPE_3__ {int /*<<< orphan*/  keyseed; int /*<<< orphan*/  (* keyproc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ;} ;
typedef  TYPE_1__ krb5_get_init_creds_ctx ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_enctype ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static krb5_error_code
pa_data_to_key_plain(krb5_context context,
		     const krb5_principal client,
		     krb5_get_init_creds_ctx *ctx,
		     krb5_salt salt,
		     krb5_data *s2kparams,
		     krb5_enctype etype,
		     krb5_keyblock **key)
{
    krb5_error_code ret;

    ret = (*ctx->keyproc)(context, etype, ctx->keyseed,
			   salt, s2kparams, key);
    return ret;
}