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
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_3__ {int /*<<< orphan*/ * certs; } ;
typedef  TYPE_1__ OCSP_BASICRESP ;

/* Variables and functions */
 int /*<<< orphan*/  X509_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_X509_new_null () ; 
 int /*<<< orphan*/  sk_X509_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int OCSP_basic_add1_cert(OCSP_BASICRESP *resp, X509 *cert)
{
    if (resp->certs == NULL
        && (resp->certs = sk_X509_new_null()) == NULL)
        return 0;

    if (!sk_X509_push(resp->certs, cert))
        return 0;
    X509_up_ref(cert);
    return 1;
}