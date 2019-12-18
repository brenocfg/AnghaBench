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
struct hx509_private_key_ops {int (* get_spki ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__* hx509_private_key ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_4__ {struct hx509_private_key_ops* ops; } ;
typedef  int /*<<< orphan*/  SubjectPublicKeyInfo ;

/* Variables and functions */
 int HX509_UNIMPLEMENTED_OPERATION ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

int
hx509_private_key2SPKI(hx509_context context,
			hx509_private_key private_key,
			SubjectPublicKeyInfo *spki)
{
    const struct hx509_private_key_ops *ops = private_key->ops;
    if (ops == NULL || ops->get_spki == NULL) {
	hx509_set_error_string(context, 0, HX509_UNIMPLEMENTED_OPERATION,
			       "Private key have no key2SPKI function");
	return HX509_UNIMPLEMENTED_OPERATION;
    }
    return (*ops->get_spki)(context, private_key, spki);
}