#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct _krb5_key_type {int /*<<< orphan*/ * (* evp ) () ;} ;
struct _krb5_key_data {TYPE_3__* key; TYPE_1__* schedule; } ;
struct _krb5_evp_schedule {int /*<<< orphan*/ * dctx; int /*<<< orphan*/ * ectx; } ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {TYPE_2__ keyvalue; } ;
struct TYPE_4__ {struct _krb5_evp_schedule* data; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 void* EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  krb5_abort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * stub1 () ; 

void
_krb5_evp_schedule(krb5_context context,
		   struct _krb5_key_type *kt,
		   struct _krb5_key_data *kd)
{
    struct _krb5_evp_schedule *key = kd->schedule->data;
    const EVP_CIPHER *c = (*kt->evp)();

    key->ectx = EVP_CIPHER_CTX_new();
    key->dctx = EVP_CIPHER_CTX_new();
    if (key->ectx == NULL || key->dctx == NULL)
	krb5_abort(context, ENOMEM, "malloc failed");

    EVP_CipherInit_ex(key->ectx, c, NULL, kd->key->keyvalue.data, NULL, 1);
    EVP_CipherInit_ex(key->dctx, c, NULL, kd->key->keyvalue.data, NULL, 0);
}