#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct _krb5_key_data {TYPE_1__* schedule; } ;
struct _krb5_evp_schedule {int /*<<< orphan*/  dctx; int /*<<< orphan*/  ectx; } ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_2__ {struct _krb5_evp_schedule* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ ) ; 

void
_krb5_evp_cleanup(krb5_context context, struct _krb5_key_data *kd)
{
    struct _krb5_evp_schedule *key = kd->schedule->data;
    EVP_CIPHER_CTX_free(key->ectx);
    EVP_CIPHER_CTX_free(key->dctx);
}