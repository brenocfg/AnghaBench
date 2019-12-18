#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  engine; } ;
typedef  TYPE_1__ EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/ * EC_KEY_copy (TYPE_1__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  EC_KEY_free (TYPE_1__*) ; 
 TYPE_1__* EC_KEY_new_method (int /*<<< orphan*/ ) ; 

EC_KEY *EC_KEY_dup(const EC_KEY *ec_key)
{
    EC_KEY *ret = EC_KEY_new_method(ec_key->engine);

    if (ret == NULL)
        return NULL;

    if (EC_KEY_copy(ret, ec_key) == NULL) {
        EC_KEY_free(ret);
        return NULL;
    }
    return ret;
}