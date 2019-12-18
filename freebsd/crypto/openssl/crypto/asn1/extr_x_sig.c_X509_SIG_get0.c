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
struct TYPE_3__ {int /*<<< orphan*/ * digest; int /*<<< orphan*/ * algor; } ;
typedef  TYPE_1__ X509_SIG ;
typedef  int /*<<< orphan*/  X509_ALGOR ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */

void X509_SIG_get0(const X509_SIG *sig, const X509_ALGOR **palg,
                   const ASN1_OCTET_STRING **pdigest)
{
    if (palg)
        *palg = sig->algor;
    if (pdigest)
        *pdigest = sig->digest;
}