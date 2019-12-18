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
struct hx509_keyset_ops {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__* hx509_context ;
struct TYPE_3__ {int ks_num_ops; struct hx509_keyset_ops** ks_ops; } ;

/* Variables and functions */
 scalar_t__ strcasecmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hx509_keyset_ops *
_hx509_ks_type(hx509_context context, const char *type)
{
    int i;

    for (i = 0; i < context->ks_num_ops; i++)
	if (strcasecmp(type, context->ks_ops[i]->name) == 0)
	    return context->ks_ops[i];

    return NULL;
}