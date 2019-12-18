#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned long (* hash_func ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {unsigned long type; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ OBJ_NAME ;

/* Variables and functions */
 int /*<<< orphan*/ * name_funcs_stack ; 
 unsigned long openssl_lh_strcasehash (int /*<<< orphan*/ ) ; 
 unsigned long sk_NAME_FUNCS_num (int /*<<< orphan*/ *) ; 
 TYPE_2__* sk_NAME_FUNCS_value (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long obj_name_hash(const OBJ_NAME *a)
{
    unsigned long ret;

    if ((name_funcs_stack != NULL)
        && (sk_NAME_FUNCS_num(name_funcs_stack) > a->type)) {
        ret =
            sk_NAME_FUNCS_value(name_funcs_stack,
                                a->type)->hash_func(a->name);
    } else {
        ret = openssl_lh_strcasehash(a->name);
    }
    ret ^= a->type;
    return ret;
}