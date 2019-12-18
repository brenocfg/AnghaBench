#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_boolean ;
struct TYPE_7__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {TYPE_1__ padata_value; } ;
struct TYPE_8__ {int include_pac; } ;
typedef  TYPE_2__ PA_PAC_REQUEST ;
typedef  TYPE_3__ PA_DATA ;
typedef  int /*<<< orphan*/  KDC_REQ ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KRB5_PADATA_PA_PAC_REQUEST ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* _kdc_find_padata (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ decode_PA_PAC_REQUEST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_PA_PAC_REQUEST (TYPE_2__*) ; 

__attribute__((used)) static krb5_boolean
send_pac_p(krb5_context context, KDC_REQ *req)
{
    krb5_error_code ret;
    PA_PAC_REQUEST pacreq;
    const PA_DATA *pa;
    int i = 0;

    pa = _kdc_find_padata(req, &i, KRB5_PADATA_PA_PAC_REQUEST);
    if (pa == NULL)
	return TRUE;

    ret = decode_PA_PAC_REQUEST(pa->padata_value.data,
				pa->padata_value.length,
				&pacreq,
				NULL);
    if (ret)
	return TRUE;
    i = pacreq.include_pac;
    free_PA_PAC_REQUEST(&pacreq);
    if (i == 0)
	return FALSE;
    return TRUE;
}