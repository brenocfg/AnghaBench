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
struct hx509_private_key_ops {int (* generate_private_key ) (int /*<<< orphan*/ ,struct hx509_generate_private_context*,int /*<<< orphan*/ *) ;} ;
struct hx509_generate_private_context {int /*<<< orphan*/  key_oid; } ;
typedef  int /*<<< orphan*/ * hx509_private_key ;
typedef  int /*<<< orphan*/  hx509_context ;

/* Variables and functions */
 int HX509_SIG_ALG_NO_SUPPORTED ; 
 int /*<<< orphan*/  hx509_clear_error_string (int /*<<< orphan*/ ) ; 
 struct hx509_private_key_ops* hx509_find_private_alg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_private_key_free (int /*<<< orphan*/ **) ; 
 int hx509_private_key_init (int /*<<< orphan*/ **,struct hx509_private_key_ops*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int stub1 (int /*<<< orphan*/ ,struct hx509_generate_private_context*,int /*<<< orphan*/ *) ; 

int
_hx509_generate_private_key(hx509_context context,
			    struct hx509_generate_private_context *ctx,
			    hx509_private_key *private_key)
{
    struct hx509_private_key_ops *ops;
    int ret;

    *private_key = NULL;

    ops = hx509_find_private_alg(ctx->key_oid);
    if (ops == NULL) {
	hx509_clear_error_string(context);
	return HX509_SIG_ALG_NO_SUPPORTED;
    }

    ret = hx509_private_key_init(private_key, ops, NULL);
    if (ret) {
	hx509_set_error_string(context, 0, ret, "out of memory");
	return ret;
    }

    ret = (*ops->generate_private_key)(context, ctx, *private_key);
    if (ret)
	hx509_private_key_free(private_key);

    return ret;
}