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
struct hx509_keyset_ops {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__* hx509_context ;
struct TYPE_4__ {int ks_num_ops; struct hx509_keyset_ops** ks_ops; } ;

/* Variables and functions */
 scalar_t__ _hx509_ks_type (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct hx509_keyset_ops** realloc (struct hx509_keyset_ops**,int) ; 

void
_hx509_ks_register(hx509_context context, struct hx509_keyset_ops *ops)
{
    struct hx509_keyset_ops **val;

    if (_hx509_ks_type(context, ops->name))
	return;

    val = realloc(context->ks_ops,
		  (context->ks_num_ops + 1) * sizeof(context->ks_ops[0]));
    if (val == NULL)
	return;
    val[context->ks_num_ops] = ops;
    context->ks_ops = val;
    context->ks_num_ops++;
}