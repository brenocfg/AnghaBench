#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* hx509_private_key ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/ * (* get_internal ) (int /*<<< orphan*/ ,TYPE_2__*,char const*) ;} ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,TYPE_2__*,char const*) ; 

BIGNUM *
_hx509_private_key_get_internal(hx509_context context,
				hx509_private_key key,
				const char *type)
{
    if (key->ops->get_internal == NULL)
	return NULL;
    return (*key->ops->get_internal)(context, key, type);
}