#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* otherName; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__ d; } ;
struct TYPE_5__ {int /*<<< orphan*/ * value; int /*<<< orphan*/ * type_id; } ;
typedef  TYPE_3__ GENERAL_NAME ;
typedef  int /*<<< orphan*/  ASN1_TYPE ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 scalar_t__ GEN_OTHERNAME ; 

int GENERAL_NAME_get0_otherName(const GENERAL_NAME *gen,
                                ASN1_OBJECT **poid, ASN1_TYPE **pvalue)
{
    if (gen->type != GEN_OTHERNAME)
        return 0;
    if (poid)
        *poid = gen->d.otherName->type_id;
    if (pvalue)
        *pvalue = gen->d.otherName->value;
    return 1;
}