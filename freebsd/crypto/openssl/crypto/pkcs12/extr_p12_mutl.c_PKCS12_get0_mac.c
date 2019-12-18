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
typedef  int /*<<< orphan*/  X509_ALGOR ;
struct TYPE_5__ {TYPE_1__* mac; } ;
struct TYPE_4__ {int /*<<< orphan*/ * iter; int /*<<< orphan*/ * salt; int /*<<< orphan*/  dinfo; } ;
typedef  TYPE_2__ PKCS12 ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  X509_SIG_get0 (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 

void PKCS12_get0_mac(const ASN1_OCTET_STRING **pmac,
                     const X509_ALGOR **pmacalg,
                     const ASN1_OCTET_STRING **psalt,
                     const ASN1_INTEGER **piter,
                     const PKCS12 *p12)
{
    if (p12->mac) {
        X509_SIG_get0(p12->mac->dinfo, pmacalg, pmac);
        if (psalt)
            *psalt = p12->mac->salt;
        if (piter)
            *piter = p12->mac->iter;
    } else {
        if (pmac)
            *pmac = NULL;
        if (pmacalg)
            *pmacalg = NULL;
        if (psalt)
            *psalt = NULL;
        if (piter)
            *piter = NULL;
    }
}