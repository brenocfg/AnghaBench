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
struct TYPE_4__ {int /*<<< orphan*/ * value; int /*<<< orphan*/ * type_id; } ;
typedef  TYPE_1__ OTHERNAME ;
typedef  int /*<<< orphan*/  GENERAL_NAME ;
typedef  int /*<<< orphan*/  ASN1_TYPE ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_TYPE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GENERAL_NAME_set0_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GEN_OTHERNAME ; 
 TYPE_1__* OTHERNAME_new () ; 

int GENERAL_NAME_set0_othername(GENERAL_NAME *gen,
                                ASN1_OBJECT *oid, ASN1_TYPE *value)
{
    OTHERNAME *oth;
    oth = OTHERNAME_new();
    if (oth == NULL)
        return 0;
    ASN1_TYPE_free(oth->value);
    oth->type_id = oid;
    oth->value = value;
    GENERAL_NAME_set0_value(gen, GEN_OTHERNAME, oth);
    return 1;
}