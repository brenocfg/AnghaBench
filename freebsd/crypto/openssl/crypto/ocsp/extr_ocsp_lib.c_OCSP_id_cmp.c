#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  serialNumber; } ;
typedef  TYPE_1__ OCSP_CERTID ;

/* Variables and functions */
 int ASN1_INTEGER_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int OCSP_id_issuer_cmp (TYPE_1__ const*,TYPE_1__ const*) ; 

int OCSP_id_cmp(const OCSP_CERTID *a, const OCSP_CERTID *b)
{
    int ret;
    ret = OCSP_id_issuer_cmp(a, b);
    if (ret)
        return ret;
    return ASN1_INTEGER_cmp(&a->serialNumber, &b->serialNumber);
}