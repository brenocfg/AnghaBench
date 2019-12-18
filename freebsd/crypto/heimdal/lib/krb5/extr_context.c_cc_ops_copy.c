#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  TYPE_1__* krb5_context ;
typedef  int /*<<< orphan*/  krb5_cc_ops ;
typedef  int /*<<< orphan*/  cc_ops ;
struct TYPE_5__ {int num_cc_ops; int /*<<< orphan*/  const** cc_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_CC_NOMEM ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  krb5_set_error_message (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int) ; 
 int /*<<< orphan*/  rk_UNCONST (int /*<<< orphan*/  const**) ; 

__attribute__((used)) static krb5_error_code
cc_ops_copy(krb5_context context, const krb5_context src_context)
{
    const krb5_cc_ops **cc_ops;

    context->cc_ops = NULL;
    context->num_cc_ops = 0;

    if (src_context->num_cc_ops == 0)
	return 0;

    cc_ops = malloc(sizeof(cc_ops[0]) * src_context->num_cc_ops);
    if (cc_ops == NULL) {
	krb5_set_error_message(context, KRB5_CC_NOMEM,
			       N_("malloc: out of memory", ""));
	return KRB5_CC_NOMEM;
    }

    memcpy(rk_UNCONST(cc_ops), src_context->cc_ops,
	   sizeof(cc_ops[0]) * src_context->num_cc_ops);
    context->cc_ops = cc_ops;
    context->num_cc_ops = src_context->num_cc_ops;

    return 0;
}