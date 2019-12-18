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
struct TYPE_3__ {int /*<<< orphan*/  responseStatus; } ;
typedef  TYPE_1__ OCSP_RESPONSE ;

/* Variables and functions */
 int ASN1_ENUMERATED_get (int /*<<< orphan*/ ) ; 

int OCSP_response_status(OCSP_RESPONSE *resp)
{
    return ASN1_ENUMERATED_get(resp->responseStatus);
}